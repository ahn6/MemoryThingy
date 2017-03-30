#include <iostream>
#include <memory>
#include<vector>
#include <limits>
#include <assert.h>

template<class T>
class TrackAllocatedMemory
{
public:
	using value_type = T;
	TrackAllocatedMemory() = default;
	
	//===================================================================================================
	~TrackAllocatedMemory()
	{
		// [Assumption] We will assume that through the allocator, we can track the number of allocations
		// and decide if there is a memory leak based on the number of deallocation & allocation
		if (mAllocations == 0)
		{
			std::cout << "No memory leak" << std::endl;
		}
		else
		{
			std::cout << "Currently, there is a memory leak.." << std::endl;
		}
	}

	//===================================================================================================
	// At some point in the program, we must tell the compiler to use our memory allocation rather than the defaults
	template<class U>
	struct rebind
	{
		using other = TrackAllocatedMemory<U>;
	};

	template<class U>
	TrackAllocatedMemory(const TrackAllocatedMemory<U> &other) 
	{}

	template<class U, class ... Args>
	void construct(U *p, Args && ...args)
	{
		new(p) U(std::forward<Args>(args)...);
	}

	template<class U, class ... Args>
	void destroy(U *p)
	{
		p->~U();
	}

	//===================================================================================================
	// Allocate Memory based on the number of items
	value_type* allocate(size_t count)
	{
		mAllocations += count;
		return static_cast<T*>(operator new(sizeof(T) * count));
	}

	//===================================================================================================
	// Deallocate Memory based on the number of items
	void deallocate(T* p, size_t count)
	{
		operator delete(p);
		mAllocations -= count;
	}

	//===================================================================================================
	// Retrieve the number of current allocations
	size_t get_allocations() const
	{
		return mAllocations;
	}
private:
	static size_t mAllocations;
};

template<class T>
typename size_t TrackAllocatedMemory<T>::mAllocations = 0;
int main()
{
	// [Assumption] The tests should be ran one at a time

	// [Test 1] We can use our memory allocation for vectors,
	// as vectors allow us to enter a memory_allocator as a parameter
	std::vector<int, TrackAllocatedMemory<int>> v(5);
	std::cout << "Testing memory allocation for vectors " << std::endl;
	std::cout << "The number of allocations for v(5) is " << v.get_allocator().get_allocations() << std::endl;


	// [Test 2] We can use our memory allocation for arrays as well
	//TrackAllocatedMemory<int> hello[10][10];
	//int *p = NULL;
	//hello[1][1].allocate(10);
	//hello[1][1].deallocate(p,10);
	//std::cout << "Testing memory allocation for arrays " << std::endl;
	//std::cout << "The number of allocations for hello[1][1] is " << hello[1][1].get_allocations() << std::endl;

	return 0;
}