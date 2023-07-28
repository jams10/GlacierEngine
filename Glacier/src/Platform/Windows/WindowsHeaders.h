#pragma once

// target Windows 7 or later
#define _WIN32_WINNT 0x0A00 // �ڵ忡�� �����ϴ� �ּ� � ü�� ������ ����.
#include <sdkddkver.h>      // �������� ������ ���� ��ũ�ε��� ���ǵǾ� �ִ� ��� ����.

// Windows.h ��� ���Ͽ��� �츮�� �ۼ��� ���ø����̼ǿ��� ������� ���� API�� ���� ����ִµ�,
// �Ʒ��� ���� ���� ��ũ�� ���Ǹ� ���� Ư�� API���� ���ܽ��Ѽ� ������ �ð��� ����ų �� �ֵ�/
#define WIN32_LEAN_AND_MEAN // ��ȣȭ, DDE, RPC, �� �� Windows ���ϰ� ���� API�� ����
//#define NOMINMAX          // Windows.h�� min, max ��ũ�ΰ� ���ǵǾ� �ִµ�, �̴� std::min, max�� �浹�ϱ� ������ ��������. ������Ʈ ��ó������ ������.
                            // ��ó���� �߰����� ���� ��� assimp ���̺귯�� ������ include �ϴ� �������� ������ ���� �߻�.

//#define STRICT            // ��ȣ�� ������ �� ������ �����ϰ� ����ϴ� �� �� �����ؾ� �ϴ� ����� ����ϵ��� ����.
                            // �ڵ� �ۼ��� �߰������� ���Ǹ� ����̰� �Ǿ� ����� �ð��� �����. Windows �ڵ忡 Ư�� ������.
#include <stdint.h>
#include <Windows.h>