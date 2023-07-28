#pragma once

namespace Glaicer
{
    /*
    *   <CustomDelegate>
    *   Ư�� ��Ȳ�� �߻� ���� ���� Ư�� �Լ����� ȣ���� �������� callback �Լ����� ���ε�, broadcast�� ���� ���ε��� �Լ����� ��� ȣ���� �� �� ����.
    */
    template <class... ARGS>
    class CustomDelegate
    {
    public:
        typedef typename std::list<std::function<void(ARGS...)>>::iterator iterator;

        // Delegate�� ���ε� �� �ݹ� �Լ����� ���ڵ��� �Ѱ��ָ鼭 ȣ������.
        void Broadcast(const ARGS... args)
        {
            for (auto& func : functions)
            {
                func(args...);
            }
        }

        // �ݹ� �Լ� ���ε�.
        CustomDelegate& operator += (std::function<void(ARGS...)> const& func)
        {
            functions.push_back(func);
            return *this;
        }

        // �ݹ� �Լ� ���ε� ����.
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
    �ڵ� ��ó : https://kukuta.tistory.com/207
    ��� �Լ� ������ : https://stackoverflow.com/questions/16521644/c11-pointers-to-member-function-using-stdfunctiontarget

    <std::function::target >

    - std::function ��ü�ȿ� ����� callable ��ü�� ���� �����͸� ���� ��.
    - �� ��, ���ø� ���ڷ� �Ѱ��� �Լ� ������ Ÿ�԰� ��ġ�� ��� �ش� callable ��ü�� ���� �����͸� �����ϰ�, �׷��� ���� ��� nullptr�� �����ϰ� ��.

    ex)
        int my_plus (int a, int b) {return a+b;}

        std::function<int(int,int)> foo = my_plus;
        foo.target<int(*)(int,int)>();  -> my_plus �Լ��� ���� �����͸� ������.
        foo.target<void(*)(int,int)>(); -> foo�� ����� �Լ� ��ü�� �Լ� �ñ״��İ� �ٸ��� ������ nullptr�� ������.

    void(* const* func_ptr)(ARGS...)
    @ ���� Ÿ���� void, ���� Ÿ���� ���ڵ��� �޾��ִ� �Լ� �����Ϳ� ���� const ������. �� �̸��� func_ptr.

    func.template target<void(*)(ARGS...)>()
    @ std::function ��ü�� func�� std::function::target �Լ��� �̿��Ͽ� ���� Ÿ���� void, ���� Ÿ���� ���ڸ� �޾��ִ� �Լ� ��ü�� ���, �ش� �Լ� �����͸� ����.
      �׷��� �ʰ� ���ø����� �Ѱ��� �Լ� Ÿ���� �ƴϸ� nullptr�� �����ϰ� ��.
    @ �� ��, 'template' Ű������ ���, target �Լ��� std::function�� ��� �Լ� ���ø�(Ŭ������ ���ø� ��� �Լ�)���� ����ϴ� Ű�����̴�.
      template Ű���带 ���� target �Լ��� ��� �Լ� ���ø����� ������ָ鼭, �Լ� ���ø��� specialize �ϱ� ���� 'void(*)(ARGS...)'�� ���ڷ� �Ѱ� �ְ� �ִ�.
      std::function�� ���ø� Ŭ�����̰�, ���ø� Ŭ������ ���ø� ��� �Լ��� ȣ���� �� template Ű���带 ���� �ش� ��� �Լ��� ���ø� �Լ����� ��������� ������,
      �����Ϸ��� �ش� ��� �Լ��� �Ϲ� ��� �Լ��� �߷��ϱ� ������ ������ ������ �߻��� �� �ִ�.

    void (* const* func_ptr)(ARGS...) = func.template target<void(*)(ARGS...)>();
    @ �����ϸ� �� �ڵ�� ���� Ÿ���� void, ���ڷδ� ���� Ÿ�Ե��� �޾��ִ� �Լ� ��ü�� ���� �����͸� target �Լ��� ���� �����Ͽ�, const �Լ� ������ func_ptr�� ������.

    Ư�� Ŭ������ ��� �Լ����� ���� �� �ڽ��� ȣ���� ��ü�� ���ڷ� �޾��ֱ� ������ ��� �Լ��� �޴� std::function ��ü�� ��� �Ʒ��� ���� �޾� �־�� ��.
    std::function<int(A&)> f1 = &A::some_func;
    ����, Ŭ���� A�� ��� ������ int�� �����ϰ� char�ϳ��� �޾� �شٸ�, std::function<int(A&, char)> f1 = &A::some_func�� ���� �տ� Ŭ������ ��ü�� �޾���.

    ��, ���� Ÿ���� void�̰� �Լ��� ���ڷ� int �ΰ��� �޾��ִ� ��� �Լ� �������� ���, void (*)(int, int)�� �ƴ� void (A::*)(int, int)�� ���ǵ�.
    ����, void (* const* func_ptr)(ARGS...) = func.template target<void(*)(ARGS...)>(); �ڵ忡�� ���ڷ� �޾��� func�� ��� �Լ��� ���, func_ptr�� nullptr�� ��.
    �̸� ���� �޾��ִ� std::function ��ü�� ��� �Լ��� ����ְ� �ִ���, �Ϲ� �Լ��� ����ְ� �ִ��� ������ �� ����.

    func.target_type().hash_code() ó�� std::function�� target_type().hash_code()�� ���� �Լ��� �ؽ� �ڵ带 ������, �Ϲ� �Լ��� ��쿡 ���� �Լ� �ñ״��ĸ� ���� ��� ����
    �ؽ� �ڵ带 �����ϱ� ������ ���� �Լ� �ñ״�ó�� ���� �Լ����� �����ϱ� ��ƴ�.
    ����, ��� �Լ��� ��쿡�� ������ �ؽ� �ڵ带 ������ ���Ͽ� �츮�� list�� �־��� �Լ� ��ü���� ������ �� �ְ�,
    �Ϲ� �Լ��� ��쿡�� std::function �Լ� ��ü�� ����� �Լ� �����͸� ���� ���ؼ� �Լ����� ������ �� �ִ�.
*/