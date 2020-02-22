#pragma once
#using <mscorlib.dll>

using namespace System;

namespace CLRCoreLibrary {
	public ref class MyNamesSplitterClass
	{
	private:
		System::String ^_FName, ^_LName;
	public:
		MyNamesSplitterClass(System::String ^FullName)
		{
			int pos = FullName->IndexOf(" ");
			if (pos < 0)
				throw gcnew System::Exception("Invalid full name!");
			_FName = FullName->Substring(0, pos);
			_LName = FullName->Substring(pos + 1, FullName->Length - pos - 1);
		}

		void Print()
		{
			Console::WriteLine("First name: {0}\nLastName: {1}", _FName, _LName);
		}

		void Arrays()
		{
			// Array creation cannot be simpler, this example will get you started:
			cli::array<int> ^a = gcnew cli::array<int> {1, 2, 3};

			// which will create an array of three integers, whereas:
			array<int> ^a2 = gcnew array<int>(100) { 1, 2, 3 };
			
			int i = 0;
			for each (int v in a2)
			{
				Console::WriteLine("value={0}", v);
				i++;
				if (i == 10)
					break;
			}

			// To create a multi - dimensional array, 3D in this case, like a 4x5x2, all initialized to zero :
			array<int, 3> ^threed = gcnew array<int, 3>(4, 5, 2);
			Console::WriteLine(threed[0, 0, 0]);
			// An array of classes of strings can be done like this:
			array<String ^> ^strs = gcnew array<String ^> {"Hello", "World"};
			
			// An array of strings initialized in a for loop[3] :
			array<String ^> ^strs2 = gcnew array<String ^>(5);
			int cnt = 0;

			// We use the tracking reference to access the references inside the array
			// since normally strings are passed by value
			for each (String ^%s in strs2)
			{
				s = gcnew String((cnt++).ToString());
			}
		}

		void ObjTest() {
			// To create a new reference of a certain class or value type, we have to allocate it with the "gcnew" keyword; for example:
			System::Object ^x = gcnew System::Object();

			// It is worthwhile noting that the "nullptr" keyword designates a null reference.In addition to the punctuator "^" symbol,
			// we have the percent "%" which stands for a tracking reference; I would like to quote the ECMA - 372:
			/*
			N* pn = new N; // allocate on native heap
			N& rn = *pn; // bind ordinary reference to native object
			R^ hr = gcnew R; // allocate on CLI heap
			R% rr = *hr; // bind tracking reference to gc-lvalue
			*/

			// !!!!!!!!!!!!
			// In general, the punctuator % is to ^ as the punctuator & is to *.
		}

		// Parameter Array
		void Avg(String ^msg, ... array<int> ^values)
		{
			int tot = 0;
			for each (int v in values)
				tot += v;
			Console::WriteLine("{0} {1}", msg, tot / values->Length);
		}

	};

	public value struct MyPoint
	{
		int x, y, z, time;
		MyPoint(int x, int y, int z, int t)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->time = t;
		}
	};

	public enum class SomeColors { Red, Yellow, Blue };

	public enum class SomeColorsTyped : char { Red = 10, Yellow, Blue };
}