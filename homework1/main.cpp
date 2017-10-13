#include <iostream>
#include <chrono>


template <typename T>
class MyVector{
public:
	struct Stack{
		T val;
		Stack* suc;
	};	
private:
	Stack* m_top;

public:
	MyVector(const T& val){
		m_top = new Stack;
		m_top->val = val;
		m_top->suc = nullptr;
	}
	MyVector(){
		m_top = nullptr;
	}

	T pop()
	{
		if(m_top == nullptr)return T();
		Stack* addr = m_top;
		T temp = addr->val;	
		m_top = m_top->suc;
		delete addr;
		return temp;	
	}
	
	void push(const T& val)
	{
		Stack* new_ptr = new Stack;
		new_ptr->val = val;
		new_ptr->suc = m_top;
		m_top = new_ptr;
	}
};

int main(void)
{
	
	int rep = 16;
	
	for(int exp=0; exp<30; exp++){

		//値の格納
		MyVector<int> vec;
		for(int i=0; i<rep; i++)vec.push(i);


		//計測開始
		auto clock_start = std::chrono::system_clock::now();
	
		int sum = 0;
		for(int i=0; i<rep; i++){
			sum += vec.pop();
		}

		//時間計測ここまで
		auto clock_end = std::chrono::system_clock::now();
	
#if 0	
		std::cout << "Repetition = " << rep << std::endl;	
		std::cout << "Sum = " << sum << std::endl;
		std::cout << "Elapsed Time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end - clock_start).count() << "[us]\n" << std::endl;
#endif	

		std::cout << rep << ", " << std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end - clock_start).count() << std::endl;
		rep *= 2;	
	}	
	return 0;
}



