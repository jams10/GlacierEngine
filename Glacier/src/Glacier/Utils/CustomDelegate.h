#pragma once

namespace Glaicer
{
    /*
    *   <CustomDelegate>
    *   특정 상황이 발생 했을 때만 특정 함수들을 호출할 목적으로 callback 함수들을 바인딩, broadcast를 통해 바인딩한 함수들을 모두 호출해 줄 수 있음.
    */
    template <class... ARGS>
    class CustomDelegate
    {
    public:
        typedef typename std::list<std::function<void(ARGS...)>>::iterator iterator;

        // Delegate에 바인딩 한 콜백 함수들을 인자들을 넘겨주면서 호출해줌.
        void Broadcast(const ARGS... args)
        {
            for (auto& func : functions)
            {
                func(args...);
            }
        }

        // 콜백 함수 바인딩.
        CustomDelegate& operator += (std::function<void(ARGS...)> const& func)
        {
            functions.push_back(func);
            return *this;
        }

        // 콜백 함수 바인딩 해제.
        CustomDelegate& operator -= (std::function<void(ARGS...)> const& func)
        {
            void (* const* func_ptr)(ARGS...) = func.template target<void(*)(ARGS...)>();
            const std::size_t func_hash = func.target_type().hash_code();

            if (nullptr == func_ptr)
            {
                for (auto itr = functions.begin(); itr != functions.end(); itr++)
                {
                    if (func_hash == (*itr).target_type().hash_code())
                    {
                        functions.erase(itr);
                        return *this;
                    }
                }
            }
            else
            {
                for (auto itr = functions.begin(); itr != functions.end(); itr++)
                {
                    void (* const* delegate_ptr)(ARGS...) = (*itr).template target<void(*)(ARGS...)>();
                    if (nullptr != delegate_ptr && *func_ptr == *delegate_ptr)
                    {
                        functions.erase(itr);
                        return *this;
                    }
                }
            }
            return *this;
        }

        iterator begin() noexcept
        {
            return functions.begin();
        }
        iterator end() noexcept
        {
            return functions.end();
        }
        void clear()
        {
            functions.clear();
        }

    private:
        std::list<std::function<void(ARGS...)>> functions;
    };
}

/*
    코드 출처 : https://kukuta.tistory.com/207
    멤버 함수 포인터 : https://stackoverflow.com/questions/16521644/c11-pointers-to-member-function-using-stdfunctiontarget

    <std::function::target >

    - std::function 객체안에 저장된 callable 객체에 대한 포인터를 리턴 함.
    - 이 때, 템플릿 인자로 넘겨준 함수 포인터 타입과 일치할 경우 해당 callable 객체에 대한 포인터를 리턴하고, 그렇지 않은 경우 nullptr를 리턴하게 됨.

    ex)
        int my_plus (int a, int b) {return a+b;}

        std::function<int(int,int)> foo = my_plus;
        foo.target<int(*)(int,int)>();  -> my_plus 함수에 대한 포인터를 리턴함.
        foo.target<void(*)(int,int)>(); -> foo에 저장된 함수 객체의 함수 시그니쳐가 다르기 때문에 nullptr를 리턴함.

    void(* const* func_ptr)(ARGS...)
    @ 리턴 타입이 void, 여러 타입의 인자들을 받아주는 함수 포인터에 대한 const 포인터. 그 이름은 func_ptr.

    func.template target<void(*)(ARGS...)>()
    @ std::function 객체인 func가 std::function::target 함수를 이용하여 리턴 타입이 void, 여러 타입의 인자를 받아주는 함수 객체일 경우, 해당 함수 포인터를 리턴.
      그렇지 않고 템플릿으로 넘겨준 함수 타입이 아니면 nullptr를 리턴하게 됨.
    @ 이 때, 'template' 키워드의 경우, target 함수가 std::function의 멤버 함수 템플릿(클래스의 템플릿 멤버 함수)임을 명시하는 키워드이다.
      template 키워드를 통해 target 함수가 멤버 함수 템플릿임을 명시해주면서, 함수 템플릿을 specialize 하기 위해 'void(*)(ARGS...)'을 인자로 넘겨 주고 있다.
      std::function이 템플릿 클래스이고, 템플릿 클래스의 템플릿 멤버 함수를 호출할 때 template 키워드를 통해 해당 멤버 함수가 템플릿 함수임을 명시해주지 않으면,
      컴파일러가 해당 멤버 함수를 일반 멤버 함수로 추론하기 때문에 컴파일 에러가 발생할 수 있다.

    void (* const* func_ptr)(ARGS...) = func.template target<void(*)(ARGS...)>();
    @ 정리하면 위 코드는 리턴 타입이 void, 인자로는 여러 타입들을 받아주는 함수 객체에 대한 포인터를 target 함수를 통해 추출하여, const 함수 포인터 func_ptr에 저장함.

    특정 클래스의 멤버 함수들은 구현 상 자신을 호출한 객체를 인자로 받아주기 때문에 멤버 함수를 받는 std::function 객체의 경우 아래와 같이 받아 주어야 함.
    std::function<int(A&)> f1 = &A::some_func;
    만약, 클래스 A의 멤버 변수가 int를 리턴하고 char하나를 받아 준다면, std::function<int(A&, char)> f1 = &A::some_func로 제일 앞에 클래스의 객체를 받아줌.

    즉, 리턴 타입이 void이고 함수의 인자로 int 두개를 받아주는 멤버 함수 포인터의 경우, void (*)(int, int)가 아닌 void (A::*)(int, int)로 정의됨.
    따라서, void (* const* func_ptr)(ARGS...) = func.template target<void(*)(ARGS...)>(); 코드에서 인자로 받아준 func가 멤버 함수인 경우, func_ptr는 nullptr가 됨.
    이를 통해 받아주는 std::function 객체가 멤버 함수를 담아주고 있는지, 일반 함수를 담아주고 있는지 구분할 수 있음.

    func.target_type().hash_code() 처럼 std::function의 target_type().hash_code()를 통해 함수의 해쉬 코드를 얻어오면, 일반 함수의 경우에 같은 함수 시그니쳐를 갖는 경우 같은
    해쉬 코드를 리턴하기 때문에 같은 함수 시그니처를 갖는 함수들을 구분하기 어렵다.
    따라서, 멤버 함수의 경우에는 간단히 해쉬 코드를 가져와 비교하여 우리가 list에 넣어준 함수 객체들을 제거할 수 있고,
    일반 함수의 경우에는 std::function 함수 객체에 저장된 함수 포인터를 직접 비교해서 함수들을 구별할 수 있다.
*/