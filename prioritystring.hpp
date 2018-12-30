#ifndef PRIORITYSTRING_HPP
#define PRIORITYSTRING_HPP

#include <string>



class PriorityString
{
public:
	int priority;
	std::string data;
};

/// for priority queue comparision
class PriorityStringComparison
{
private:
	bool reverse;
public:
	PriorityStringComparison(const bool& revparam = false)
	{
		reverse = revparam;
	}
	bool operator() (const PriorityString lhs, const PriorityString rhs) const
	{
		if (reverse)
			return (lhs.priority > rhs.priority);
		else
			return (lhs.priority < rhs.priority);
	}

	/*
		//auto lamComp = [](PriorityString left, PriorityString right) { return (left.priority ^ 1) < (right.priority ^ 1); };
//	struct compSort
//	{
//		auto operator()(PriorityString const& a, PriorityString const& b)
//			-> bool
//		{
//			return (a.priority < b.priority);
//		}
//	};
	//typedef std::priority_queue<PriorityString, std::vector<PriorityString>, decltype(lamComp)>  pq;
*/

};


#endif // !PRIORITYSTRING_HPP

