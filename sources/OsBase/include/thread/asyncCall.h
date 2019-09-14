#ifndef ASYNCCALL_H__
#define ASYNCCALL_H__

/***********************************************************************************************************************
Description         : async all any function
Author              : Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
Copyright           : free to use / modify / sale in free and commercial software with those head comments.
***********************************************************************************************************************/
#include <MiniMPL\callbacker.hpp>
#define THREAD_NUMBER_IN_POOL       1

enum EAsyncMode {
    EAsync_NewThread,               //job runs in independent new thread
    EAsync_ShareAuto,               //job runs in shared thread by workload balance
    EAsync_ShareFixTheadIdx,        //job runs in shared thread with specified thread index , MUST be lesser or equal than EAsync_ShareMaxThreadIdx
    EAsync_ShareMaxThreadIdx=EAsync_ShareFixTheadIdx+THREAD_NUMBER_IN_POOL-1     //max shared thread index
};
void asyncExecute(MiniMPL::TpCallbacker const& pCallback,EAsyncMode eMode=EAsync_ShareAuto);
void discardJobs();

#endif // ASYNCCALL_H__
