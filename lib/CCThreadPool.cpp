#include"CCThreadPool.h"
#include<memory>	//make_unique
#include<mutex>
#include<utility>	//move
#include<vector>
using namespace std;

namespace nTool
{
	CThreadPool::CThreadPool(const size_t count)
		:mut_{new mutex()},size_{count},thr_{new CThreadPoolItem<void>[count]()}
	{
		for(auto p{thr_};p!=thr_+count;++p)
		{
			p->setCommun(make_unique<CThreadPoolCommun>(p,join_anyList_,waitingQue_,id_++));
			waitingQue_.emplace(id_.get(),p);
		}
	}

	void CThreadPool::join_all()
	{
		for(size_t i{0};i!=count();++i)
			if(joinable(i))
				join(i);
	}

	size_t CThreadPool::join_any()
	{
		auto temp{join_anyList_.wait_and_pop()};
		const auto id{temp.first};
		temp.second->join();
		return id;
	}

	void CThreadPool::wait_until_all_available() const
	{
		lock_guard<mutex> lock{*mut_};
		vector<typename CThreadPoolCommun::pair> vec;
		vec.reserve(count());
		for(size_t i{0};i!=count();++i)
			vec.emplace_back(waitingQue_.wait_and_pop());
		for(auto &val:vec)
			waitingQue_.emplace(move(val));
	}

	CThreadPool::~CThreadPool()
	{
		delete []thr_;	//CThreadPoolItem is RAII, you don't have to call join_all()
		delete mut_;
	}
}