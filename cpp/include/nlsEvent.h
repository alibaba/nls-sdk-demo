/*
 * Copyright 2015 Alibaba Group Holding Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NLS_SDK_EVENT_H
#define NLS_SDK_EVENT_H

#ifdef _WINDOWS_COMPILE_
#ifndef  ASR_API
#define ASR_API _declspec(dllexport)
#endif
#else
#define ASR_API
#endif

#include <string>
#include <vector>

class ASR_API NlsEvent {
public:

enum EventType {
    TaskFailed = 0,
    RecognitionStarted = 1,
    RecognitionCompleted = 2,
    RecognitionResultChanged = 3,
    SynthesisCompleted = 4,
    Binary = 5,
    VerificationStarted = 6,
    VerficationCompleted = 7,
    WakeWordVerificationCompleted = 8,
    DialogResultGenerated = 9,
#pragma region VPM
    RegistrationStarted = 10,
    RegistrationCompleted = 11,
    Deleted = 12,
#pragma endregion
    VoiceRecognitionCompleted = 13,
    Close = 14
};

/**
    * @brief NlsEvent构造函数
    * @param event    NlsEvent对象
    */
NlsEvent(NlsEvent&  event);

/**
    * @brief NlsEvent构造函数
    * @param msg    Event消息字符串
    * @param code   Event状态编码
    * @param type    Event类型
    */
NlsEvent(std::string msg, int code, EventType type);

/**
    * @brief NlsEvent构造函数
    * @param data    二进制数据
    * @param code   Event状态编码
    * @param type    Event类型
    * @return
    */
NlsEvent(std::vector<unsigned char> data, int code, EventType type);

/**
    * @brief NlsEvent析构函数
    */
~NlsEvent();

/**
    * @brief 获取状态码
    * @note 正常情况为0或者200，失败时对应失败的错误码。错误码参考SDK文档说明。
    * @return string
    */
std::string getStausCode();

/**
    * @brief 获取云端返回的结果
    * @note json格式
    * @return string
    */
std::string getResponse();

/**
    * @brief 获取NlsRequest操作过程中出现失败时的错误信息
    * @note 在Failed回调函数中使用
    * @return string
    */
std::string getErrorMessage();

/**
    * @brief 获取云端返回的二进制数据
    * @note 仅用于语音合成功能
    * @return vector<unsigned char>
    */
std::vector<unsigned char> getBinaryData();

/**
    * @brief 获取当前所发生Event的类型
    * @note Event值参照NlsClient.h说明
    * @return EventType
    */
EventType getMsgType();

private:

int _errorcode;
std::string _msg;
EventType _msgtype;
std::vector<unsigned char> _binaryData;

};

typedef void(*NlsCallbackMethod)(NlsEvent*, void*);

#endif //NLS_SDK_EVENT_H
