#include<iostream>
#include "MamatScriptEngine.h"
#include "VariablesMap.h"
#include "MySharedPtr.h"
#include "Scalar.h"
#include "Matrix.h"

using namespace std;

int main() {
	VariablesMap varMap;
	MamatScriptEngine mmtEng(cin, varMap);

	while (!cin.eof())
	{
		try
		{
			mmtEng.Execute();
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unexpected Error" << endl;
			return 1;
		}
	}

	return 0;
}



	/////////////////////////////////////////////////////////////////////////////////
	//try
	//{
	//	MySharedPtr<int> p1(new int); // p1 counter=1 
	//	*p1 = 0; // the value pointed to by p1 is changed to 0 
	//	cout << (*p1) << endl; // prints the value pointed to by p1 (prints 0) 
	//	cout << (*(p1.get())) << endl; // same as previous line 
	//	MySharedPtr<int> p2(p1); // p1/p2 counter=2 
	//	MySharedPtr<int> p3(new int); // p3 counter =1 
	//	p3 = p1; // p3/p2/p1 counter=3, previous p3 object deleted 
	//	MySharedPtr<int> p4(new int); // p4 counter =1 
	//	p2 = p4; // p2/p4 counter = 2, p1/p3 counter = 2, no object is deleted
	//	p1 = p2; // p1/p2/p4 counter =3, p3 counter = 1, no object is deleted 
	//	return 0;
	//}
	//catch (const exception& e)
	//{
	//	cout << e.what() << endl;
	//}

	/////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////
	//// Test Scalar, Mat:
//
//VarPtr p1(new Scalar(3));
//VarPtr p2(new Matrix(3, 5, 2));
//VarPtr p3(new Scalar(2));
//p3 = (*p1) + (*p2);
//cout << p3 << endl;
//
	//Scalar scl1(1);
	//Scalar scl2(1);
	//VarPtr pScl1 = &scl1;

	//VarPtr pScl2 = &scl2;
	//(*pScl2.get())[1] = 2;
	//VarPtr pScl3 = pScl1;
	//VarPtr pScl4 = pScl1->Copy();

	//pScl4 = pScl1;

	//cout << pScl4;
	//cout << pScl4->Transpose();

	//VarPtr pscl_m = (*pScl2.get()) * (*pScl1.get());
	//cout << pscl_m;

	//VarPtr pscl_m1 = (*pScl2.get()) + (*pScl1.get());
	//cout << pscl_m1;

	//VarPtr p_nEl1 = pScl1->NumElems();
	//cout << p_nEl1;

	//VarPtr p_sz1 = pScl1->Size();
	//cout << p_sz1;

	//Matrix mat1(2, 3, 0);
	//VarPtr pMat1 = &mat1;
	//(*pMat1.get())[1] = 1;
	//(*pMat1.get())[2] = 4;
	//(*pMat1.get())[3] = 2;
	//(*pMat1.get())[4] = 5;
	//(*pMat1.get())[5] = 3;
	//(*pMat1.get())[6] = 6;
	//cout << pMat1;
	//cout << endl;
	//cout << pMat1->Transpose();
	//cout << pMat1->Size(2);

	////Matrix mat2(3, 1, 0);
	////VarPtr pMat2 = &mat2;
	////(*pMat2.get())[1] = 1;
	////(*pMat2.get())[2] = -1;
	////(*pMat2.get())[3] = 2;

	//Matrix mat2(2, 3, 0);
	//VarPtr pMat2 = &mat2;
	//(*pMat2.get())[1] = 1;
	//(*pMat2.get())[2] = -1;
	//(*pMat2.get())[3] = 0;
	//(*pMat2.get())[4] = 8;
	//(*pMat2.get())[5] = -5;
	//(*pMat2.get())[6] = 10;

	//cout << "M1 = " << endl;
	//cout << pMat1;
	//cout << "M2 = " << endl;
	//cout << pMat2;
	//cout << "----------------------" << endl;
	//cout << endl;

	//std::cout << typeid(*pMat1).name() << endl;
	//string str1 = typeid(*pMat1).name();

	////cout << (*pMat1.get()) * (*pMat2.get());
	////cout << endl;

	////cout << ((*pScl1.get())[2]) << endl;

	////cout << (*pMat2.get()) * (*pMat1.get());
	////cout << endl;

	//cout << pMat1 << endl;

	//cout << (*pScl2.get()) * (*pMat1.get());
	//cout << endl;

	//cout << (*pMat1.get()) * (*pScl2.get());
	//cout << endl;

	//cout << (*pMat1.get()) + (*pMat2.get());
	//cout << endl;

	//cout << ((*pMat1.get()) < (*pMat2.get()));
	//cout << endl;
	//
	//cout << ((*pMat1.get()) > (*pMat2.get()));
	//cout << endl;

	//Matrix mat3(2, 3, -1);
	//VarPtr pMat3 = &mat3;
	//(*pMat3.get())[3] = 10;

	//cout << endl;
	//cout << "Mat1 = " << endl;
	//cout << pMat1;
	//cout << endl;
	//cout << "Mat3 = " << endl;
	//cout << pMat3;

	//cout << endl;
	//cout << "+ :" << endl;
	//cout << (*pMat1.get()) + (*pMat3.get());
	//cout << endl;

	//cout << "< :" << endl;
	//cout << ((*pMat1.get()) < (*pMat3.get()));
	//cout << endl;

	//cout << "< :" << endl;
	//cout << ((*pMat1.get()) > (*pMat3.get()));
	//cout << endl;
	///////////////////////////////////////////////////////////////////////////////////


	//VariablesMap varMap;
	//MamatScriptEngine mmtEng(cin, varMap);

	//while (!cin.eof())
	//{
	//	try
	//	{
	//		mmtEng.Execute();
	//	}
	//	catch (const exception& e)
	//	{
	//		cout << e.what() << endl;
	//	}
	//	catch (...)
	//	{
	//		cout << "Unexpected Error" << endl;
	//		return 1;
	//	}
	//}
	//
	//return 0;

