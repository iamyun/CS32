#include <iostream>
#include <string>
using namespace std;

class SmartPhone
{
public:
	SmartPhone(string future)
	{
		m_future = future;
	}

	virtual ~SmartPhone() {}

	virtual string name() const = 0;

	virtual void printWebBrowser() const = 0;

	string futureMove() const
	{
		return m_future + " market share";
	}

private:
	string m_future;
};

class Windows : public SmartPhone
{
public:
	Windows(string name)
		:SmartPhone("tries to maintain its")
	{
		m_name = name;
	}

	virtual ~Windows()
	{
		cout << "Destroying " << m_name << " the Windows" << endl;
	}

	virtual string name() const
	{
		return m_name;
	}

	virtual void printWebBrowser() const
	{
		cout << "IE";
	}

private:
	string m_name;
};

class iOS : public SmartPhone
{
public:
	iOS(string name, string version)
		:SmartPhone("continues to lose")
	{
		m_name = name;
		m_version = version;
	}

	virtual ~iOS()
	{
		cout << "Destroying " << m_name << " the iOS" << endl;
	}

	virtual string name() const
	{
		return m_name;
	}

	virtual void printWebBrowser() const
	{
		cout << "Safari version " << m_version;
	}

private:
	string m_name;
	string m_version;
};

class Android : public SmartPhone
{
public:
	Android(string name)
		:SmartPhone("tries to gain")
	{
		m_name = name;
	}

	virtual ~Android()
	{
		cout << "Destroying " << m_name << " the Android" << endl;
	}

	virtual string name() const
	{
		return m_name;
	}

	virtual void printWebBrowser() const
	{
		cout << "Chrome";
	}

private:
	string m_name;
};

void availability(const SmartPhone* cp)
{
	cout << cp->name() << ", using ";
	cp->printWebBrowser();
	cout << ", " << cp->futureMove() << "." << endl;
}

int main()
{
	SmartPhone* phones[4];
	phones[0] = new Windows("Alcatel OneTouch Fierce XL with Windows 10");
	// iOS has a name and initial version number for the Safari Browser 
	phones[1] = new iOS("iPhone 6 Plus", "10.0 beta 2");
	phones[2] = new Android("Samsung Galaxy S7");
	phones[3] = new Android("HTC 10");

	cout << "The SmartPhones availability!" << endl;
	for (int k = 0; k < 4; k++)
		availability(phones[k]);

	// Clean up the SmartPhones before exiting
	cout << "Cleaning up" << endl;
	for (int k = 0; k < 4; k++)
		delete phones[k];
}