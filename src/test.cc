#pragma once
#include "test.h"
#include <galaxy/GalaxyApi.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <functional>
#include <algorithm>
#include <memory>
/* 
* `<algorithm>`是所有STL头文件中最大的一个，范围涉及到比较、 交换、查找、遍历操作、复制、修改等等
* `<numeric>`体积很小，只包括几个在序列上面进行简单数学运算的模板函数
* `<functional>`定义了一些模板类,用以声明函数对象。
 */
/* 
算术生成算法属于小型算法，使用时包含的头文件为 `#include <numeric>`
 */
// C:\Users\daxia\workspace\dogdogbom\deps\gog_sdk\Libraries
#pragma comment(lib, "../deps/gog_sdk/Libraries/Galaxy64.lib")

using namespace std;

int call_result1 = 0;
int call_result2 = 0;
auto call_result3 = 0;
auto call_result4= 0;
namespace
{
	static char* client_id = "";
	static char* client_secret = "";
}

/* 异步回调绑定 */
class JsCallback : public Napi::AsyncWorker 
{
	public:
		JsCallback(Napi::Function &callback, int runTime = 1) : AsyncWorker(callback), runTime(runTime)
		{

		};
		virtual ~JsCallback(){};
		void Execute()
		{	
			std::this_thread::sleep_for(std::chrono::seconds(runTime));
			if (runTime == 4)
			{
				// SetError("failed after 'working' 4 seconds.");
			// 	Napi::Array arr = Napi::Array::New(Env(),3);
			// arr.Set(Napi::Number::New(Env(), 0), Napi::String::New(Env(), "test2"));
			// arr.Set(Napi::Number::New(Env(), 1), Napi::String::New(Env(), "test2"));
			// arr.Set(Napi::Number::New(Env(), 2), Napi::Number::New(Env(), 456));
			//把数组对象传递给回调方法
			// Callback().Call({Env().Null(), arr});
			}
		};
		void OnOK()
		{
			Napi::Array arr = Napi::Array::New(Env(),3);
			arr.Set(Napi::Number::New(Env(), 0), Napi::Number::New(Env(), call_result1));
			arr.Set(Napi::Number::New(Env(), 1), Napi::Number::New(Env(), call_result2));
			arr.Set(Napi::Number::New(Env(), 2), Napi::Number::New(Env(), call_result3));
			arr.Set(Napi::Number::New(Env(), 3), Napi::Number::New(Env(), call_result4));
			//把数组对象传递给回调方法
			Callback().Call({Env().Null(), arr});
		};
		int runTime;
};

class Ginit : public std::enable_shared_from_this<Ginit>
{
    public:
		void ListenerRegist() 
		{
			// 绑定事件： 
			cout << "listenerRegistrar:" << int(3) << endl;
			listeners.emplace_back(std::make_unique<AuthListener>(shared_from_this()));
			cout << "listenerRegistrar:" << int(31) << endl;

			// listeners.emplace_back(std::make_unique<GameJoinRequestedListener>(shared_from_this()));
			
			Shutdown();
			cout << "listenerRegistrar:" << int(32) << endl;

		}
        void Init()
		{
			cout << "listenerRegistrar1:" << int(2) << endl;
			try
			{
				cout << "listenerRegistrar1:" << int(41) << endl;
				
				cout << "init: " << client_id << " , " << client_secret << endl;
				galaxy::api::Init({client_id, client_secret});
				if (galaxy::api::GetError()) {
					cout << "GetError:" << int(1) << endl;
				} else {
					cout << "GetError:ok" << int(222) << endl;
				}
				cout << "listenerRegistrar1:" << int(42) << endl;

				IsFullyInitialized = true;
				cout << "listenerRegistrar1:" << int(43) << endl;
				bool logs{galaxy::api::User()->SignedIn()};
				call_result1 = logs ? 8 : 9;
				if (galaxy::api::GetError()) {
					cout << "GetError:" << int(3) << endl;
				} else {
					cout << "GetError:ok" << int(444) << endl;
				}
				cout << "log" << logs << endl;
				galaxy::api::User()->SignInGalaxy(true);
				bool isLogged = galaxy::api::User()->IsLoggedOn();
				call_result2 = isLogged ? 88 : 99;

				cout << "isLogged: " << isLogged << endl;
				galaxy::api::GalaxyID GalaxyID = galaxy::api::User()->GetGalaxyID().ToUint64();
				// call_result3 = GalaxyID

				const uint64_t realID = GalaxyID.GetRealID();
				call_result4 = realID;
				cout << "GetRealID: " << realID << endl;

				// galaxy::api::User()->SignInGalaxy();
				// bool isLogged = galaxy::api::User()->IsLoggedOn();
				// cout << "isLogged: " << isLogged << endl;
				// galaxy::api::GalaxyID GalaxyID = galaxy::api::User()->GetGalaxyID();
				// const uint64_t realID = GalaxyID.GetRealID();
				// cout << "realID: " << realID << endl;
				// // return Napi::Number::New(env, realID);
				// auto error = galaxy::api::GetError();
				// if (error != NULL) {
				// cout << "error: " << error->GetMsg() << error->GetName()
				// 	<< error->GetType() << endl;
				// }
				// ListenerRegist();
				cout << "listenerRegistrar1:" << int(44) << endl;

			}
			catch (const galaxy::api::IError& error)
			{
				IsFullyInitialized = false;
				cout << "listenerRegistrar1:" << int(5) << error.GetMsg() << endl;

			}
		}
		void Shutdown() {
			cout << "Shutdown:" << int(6) << endl;

			// galaxy::api::Shutdown();
		}
		void callbacktest() 
		{
			
		}
		
		// 初始化状态
		bool IsFullyInitialized;
		// listeners对象
		std::vector<std::unique_ptr<galaxy::api::IGalaxyListener>> listeners;
		// static JsCallback *asyncWorker = NULL inline;
		// 存储临时数据
		// jsFunArr
		// vector jsFunArr{}
		// 调用js回调
		// JsCallback() 
		// {
			
		// }
	private: 
		class AuthListener : public galaxy::api::GlobalAuthListener
		{
		public:

			AuthListener(const std::shared_ptr<Ginit>& game);

			void OnAuthSuccess();
			void OnAuthFailure(FailureReason reason);
			void OnAuthLost();

		private:
			std::shared_ptr<Ginit> game;
		};
};

Ginit::AuthListener::AuthListener(const std::shared_ptr<Ginit>& _game)
	: game(_game)
{
			cout << "AuthListener:" << int(7) << endl;
}

void Ginit::AuthListener::OnAuthSuccess()
{
			cout << "OnAuthSuccess:" << int(7) << endl;
}

void Ginit::AuthListener::OnAuthFailure(FailureReason reason)
{
			cout << "OnAuthFailure:" << int(9) << endl;
}

void Ginit::AuthListener::OnAuthLost()
{
			cout << "OnAuthLost:" << int(10) << endl;
}

Ginit games;

Napi::Value ginit(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
    Napi::EscapableHandleScope scope(env);
	// cout << "166" << endl; 
	string clientIDStr = info[1].As<Napi::String>().Utf8Value();
    client_id = (char*)clientIDStr.c_str();
    string clientSecretStr = info[2].As<Napi::String>().Utf8Value();
    client_secret = (char*)clientSecretStr.c_str();
    cout << "clientID: " << client_id << endl;
    cout << "clientSecret: " << client_secret << endl;
	games.Init();
	// cout << "167" << endl; 
    //格式化输入参数为浮点类型并累加
    // double arg = info[1].As<Napi::Number>().DoubleValue();
	// cout << "168" << endl; 
	// cout << "info env arg: " << arg << endl;
	// cout << "169" << endl; 
    if (info.Length() < 0)
        return Napi::Boolean::New(env, false);
    if (!info[0].IsFunction())
        return Napi::Boolean::New(env, false);
    auto jscb = info[0].As<Napi::Function>();

    //回调函数入参
    napi_value a, b;
    napi_create_double(env, 1, &a);
    napi_create_double(env, 2, &b);

    napi_value argv[] = { a, b };

    //回调函数返回值
    napi_value result;
    napi_call_function(env, env.Global(), jscb, 2, argv, &result);
	return Napi::String::New(env, "999");

    // return Napi::Value(env, result);

    // return Napi::Number::New(env, 1);
}; 

Napi::Value AsyncMethod(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    //接收Object类型的参数
    Napi::Object runInfo = info[0].As<Napi::Object>();
    //此Object类型的参数必定包含timeSpan和callBack两个属性
    // if (runInfo.Get("callBack").IsNothing() || runInfo.Get("callBack").IsNothing()) {
    //     Napi::TypeError::New(env, "Wrong arguments Type").ThrowAsJavaScriptException();
    //     return env.Null();
    // }
	int timeSpan = runInfo.Get("timeSpan").As<Napi::Number>();
    //callBack属性为回调方法类型
    Napi::Function callback = runInfo.Get("callBack").As<Napi::Function>();
    //实例化自定义的异步处理对象，把timeSpan和callBack传递给异步处理对象
    JsCallback *asyncWorker = new JsCallback(callback, timeSpan);
    //开始执行异步任务
    asyncWorker->Queue();
    //返回一个对象，此对象包含msg属性，msg属性的值为字符串please wait...
    Napi::Object obj = Napi::Object::New(env);
    obj.Set(Napi::String::New(env, "msg"), Napi::String::New(env, "please wait..."));
    return obj;
};

// Napi::Value shutdown(const Napi::CallbackInfo& info) {
// 	Napi::Env env = info.Env();
//     // Napi::EscapableHandleScope scope(env);
//     return Napi::String::New(env, '2');
// }; 

// 绑定js callback  TODO
// Napi::Value bindjsregister(const Napi::CallbackInfo& info) {
    
// }