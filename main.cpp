#include <iostream>
#include <vector> 
#include <algorithm> 
#include <cstdlib> 
#include <cstring> 

#include <boost/signals2.hpp>
//#include <boost/signals.hpp> 将被废弃，signals2最大区别是线程安全

#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp> 
#include <boost/shared_ptr.hpp> 
#include <boost/shared_array.hpp> 
#include <boost/ptr_container/ptr_vector.hpp> 

#include <boost/bind.hpp> 
#include <boost/function.hpp> 

#include <boost/algorithm/string.hpp> 
#include <boost/format.hpp> 

#include <boost/thread.hpp> 

#include <boost/filesystem.hpp> 
#include <boost/filesystem/fstream.hpp> 

#include <boost/date_time/gregorian/gregorian.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp> 

#include <boost/cast.hpp> 

void smart_point_test(){
	// 作用域指针
	/*
	   boost::scoped_ptr<int> i(new int); 
	 *i = 1; 
	 std::cout << *i.get() <<std::endl;
	 *i.get() = 2;  //获取指针地址
	 std::cout << *i.get() <<std::endl;
	 i.reset(new int);  // 重设指针，释放所指对象
	 */

	// 作用域数组
	/*
	   boost::scoped_array<int> i(new int[2]); 
	 *i.get() = 1; 
	 std::cout << i[0]<<i[1] <<std::endl;
	 i[1] = 2; 
	 std::cout << i[0]<<i[1] <<std::endl;
	 i.reset(new int[3]);
	 */

	//共享指针，使用率最高的智能指针
	//智能指针 boost::shared_ptr 基本上类似于 boost::scoped_ptr。 关键不同之处在于 boost::shared_ptr 不一定要独占一个对象。 它可以和其他 boost::shared_ptr 类型的智能指针共享所有权。 在这种情况下，当引用对象的最后一个智能指针销毁后，对象才会被释放。
	//因为所有权可以在 boost::shared_ptr 之间共享，任何一个共享指针都可以被复制，这跟 boost::scoped_ptr 是不同的
	/*
	   std::vector<boost::shared_ptr<int> > v; 
	   v.push_back(boost::shared_ptr<int>(new int(1))); 
	   v.push_back(boost::shared_ptr<int>(new int(2))); 
	   boost::shared_ptr<int> i1(new int(1)); 
	   boost::shared_ptr<int> i2(i1); //本例中定义了2个共享指针 i1 和 i2，它们都引用到同一个 int 类型的对象。i1 通过 new 操作符返回的地址显示的初始化，i2 通过 i1 拷贝构造而来。 i1 接着调用 reset()，它所包含的整数的地址被重新初始化。不过它之前所包含的对象并没有被释放，因为 i2 仍然引用着它。 智能指针 boost::shared_ptr 记录了有多少个共享指针在引用同一个对象，只有在最后一个共享指针销毁时才会释放这个对象 
	   i1.reset(new int(2));
	   */

	// 共享数组
	/*
	   boost::shared_array<int> i1(new int[2]); 
	   boost::shared_array<int> i2(i1); 
	   i1[0] = 1; 
	   std::cout << i2[0] << std::endl;  
	   */

	// 弱指针，需要配合共享指针使用
	// 当函数需要一个由共享指针所管理的对象，而这个对象的生存期又不依赖于这个函数时，就可以使用弱指针。 只要程序中还有一个共享指针掌管着这个对象，函数就可以使用该对象。 如果共享指针复位了，就算函数里能得到一个共享指针，对象也不存在了	

	// 共享容器
	// 与标准库容器+共享指针的行为相同，第一，反复声明 boost::shared_ptr 需要更多的输入。 其次，将 boost::shared_ptr 拷进，拷出，或者在容器内部做拷贝，需要频繁的增加或者减少内部引用计数，这肯定效率不高。
	// boost::ptr_vector 独占它所包含的对象，因而容器之外的共享指针不能共享所有权，这跟 std::vector<boost::shared_ptr<int> > 相反
	// 除了 boost::ptr_vector 之外，专门用于管理动态分配对象的容器还包括：boost::ptr_deque， boost::ptr_list， boost::ptr_set， boost::ptr_map， boost::ptr_unordered_set 和 boost::ptr_unordered_map
	/*
	   boost::ptr_vector<int> v; 
	   v.push_back(new int(1)); 
	   v.push_back(new int(2)); 
	   */
}

void add(int i, int j) 
{ 
	std::cout << i + j << std::endl; 
} 

bool compare(int i, int j) 
{ 
	return i > j; 
} 

void add2(int i, int j, std::ostream &os) 
{ 
	os << i + j << std::endl; 
} 

void func_object_test(){
	// boost::bind()
	std::vector<int> v; 
	v.push_back(1); 
	v.push_back(3); 
	v.push_back(2); 
	std::for_each(v.begin(), v.end(), boost::bind(add, 10, _1));
	std::sort(v.begin(), v.end(), boost::bind(compare, _1, _2)); 

	// boost::ref()
	std::for_each(v.begin(), v.end(), boost::bind(add2, 10, _1, boost::ref(std::cout))); 

	// boost::function
	boost::function<int (const char*)> f = std::atoi; 
	std::cout << f("1609") << std::endl; 
	f = std::strlen; 
	std::cout << f("1609") << std::endl; 
}

void func1() 
{ 
	std::cout << "Hello" << std::flush; 
} 

void func2() 
{ 
	std::cout << ", world!" << std::endl; 
} 

void signal_test(){
	// s 信号绑定函数func1 和func2
	boost::signals2::signal<void ()> s; 
	s.connect(func1); 
	s.connect(func2); 
	s(); // 触发就执行 
}

void string_test(){
	// string test	
	std::string s = "Boris Schäling"; 
	std::cout << boost::algorithm::to_upper_copy(s) << std::endl; 
	std::cout << boost::algorithm::erase_all_copy(s, "i") << std::endl; 
	std::cout << boost::algorithm::find_first(s, "i") << std::endl; 
	std::vector<std::string> v; 
	v.push_back("Boris"); 
	v.push_back("Schäling"); 
	std::cout << boost::algorithm::join(v, " ") << std::endl;
	std::cout << "." << boost::algorithm::trim_left_copy(s) << "." << std::endl;
	std::cout << boost::format("%1%.%2%.%3%") % 16 % 9 % 2008 << std::endl; 
}

void hello() 
{ 
	for (int i = 0; i < 5; ++i) 
	{ 
		std::cout << i << std::endl; 
	} 
} 

void thread_test() {
	//boost::thread myThread(hello);
} 

void file_system_test(){
	// write
	boost::filesystem::path p("/home/ubuntu/worksp/demo/test.txt"); 
	boost::filesystem::ofstream ofs(p); 
	ofs << "===>" << std::endl;

	// read
	boost::filesystem::ifstream ifs(p.string().c_str());
	assert(ifs.is_open());
	std::cout<<ifs.rdbuf()<< std::endl;
}

void date_time_test(){
	// 获取时间戳
	boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));
	boost::posix_time::time_duration time_from_epoch = boost::posix_time::second_clock::universal_time() - epoch;
	std::cout<<time_from_epoch.total_seconds()<< std::endl;
}

struct father 
{ 
	virtual ~father() { }; 
}; 

struct mother 
{ 
	virtual ~mother() { }; 
}; 

struct child : 
	public father, 
	public mother 
{ 
}; 

void func(father *f) 
{ 
	child *c = boost::polymorphic_downcast<child*>(f); 
} 

void cast_test() 
{ 
	child *c = new child; 
	func(c); 

	father *f = new child; 
	mother *m = boost::polymorphic_cast<mother*>(f); 
} 

int main() {
	smart_point_test();
	func_object_test();
	signal_test();
	string_test();
	thread_test();
	file_system_test();
	date_time_test();
	cast_test();
	return 0;
}
