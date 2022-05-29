#pragma once

template <typename T>
class Singletone
{
private:
	static T* m_pThis;
protected:
	Singletone() {};
	virtual ~Singletone() {};
public:
	static T* GetInstance()
	{
		if (nullptr == m_pThis)
			m_pThis = new T;
		return m_pThis;
	}

	static void DestroyInstance()
	{
		if (m_pThis)
		{
			delete m_pThis;
			m_pThis = nullptr;
		}
	}
};

template<typename T>
T* Singletone<T>::m_pThis = nullptr;
