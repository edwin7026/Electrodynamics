#include<iostream>
#include<cmath>

#define PI 3.1415

const long double k=9*pow(10, 9);

using namespace std;

struct vect
{
    long double vec[3]={0, 0, 0};

    void in_pos()           //Gather positon
    {
        cout<<"\nx = ";
        cin>>vec[0];
        cout<<"y = ";
        cin>>vec[1];
        cout<<"z = ";
        cin>>vec[2];
    }

    //Vector arithmetic

    void m_sub(vect &A, vect &B)                  //Vector subtraction
    {
        for(int i=0; i<2; i++)
        {   vec[i]=A.vec[i]-B.vec[i];
        }
    }

    void m_add(vect &A, vect &B)                  //Vector addition
    {
        for(int i=0; i<2; i++)
        {   vec[i]=A.vec[i]+B.vec[i];
        }
    }

    void m_sprod(long double c)                 //Multiplication by a scalar
    {
        for(int i=0; i<2; i++)
        {   vec[i]=vec[i]*c;
        }
    }

    void m_dotprod(vect &A, vect &B)
    {
        long double norm=0;

        for(int i=0; i<3; i++)
        {
            norm=norm+(vec[i]*vec[i]);
        }
    }

    void m_crossprod(vect &A)
    {

    }

    long double m_norm()                    //Find the norm of the vector
    {
        long double norm=0;

        for(int i=0; i<3; i++)
        {
            norm=norm+(vec[i]*vec[i]);
        }

        return sqrt(norm);

    }

    void ztransform(long double theta)          //transform the vector by theta radians in anticlockwise dir. keeping the z coordinate constant
    {
        vec[0]=vec[0]*cos(theta)-vec[1]*sin(theta);
        vec[1]=vec[0]*sin(theta)+vec[1]*cos(theta);
    }


};

struct charge
{
    long double q;
    vect pos;
    charge *next;

    void inCharge()
    {
        cout<<"Enter charge: ";
        cin>>q;
    }

};

charge *head=NULL, *tail=NULL;

struct efield               //Electric field calculation
{
    vect vectE;
    long double mag;

    void field_calc(vect &test_vect, charge *ptr)
    {
        vect temp;
        //Field calculation
        while(ptr!=NULL)
        {

                temp.m_sub(test_vect, ptr->pos);
                temp.m_sprod((ptr->q)/temp.m_norm());

                vectE.m_add(temp, vectE);

                ptr=ptr->next;

        }

        mag=k*vectE.m_norm();
        vectE.m_sprod(1/mag);
    }

    void print()
    {
        cout<<endl<<mag<<" N/C"<<endl;
    }
};

void create_charge(charge &temp_q)
{
    //Here we create a list of charges with their position

    charge *temp=new charge;
    *temp=temp_q;

    if(head==NULL)
    {
        head=temp;
        tail=temp;
    }
    else
    {
        tail->next=temp;
        tail=temp;
        tail->next=NULL;
    }
}

void poly_charge(int n, charge &temp_q)
{

    //Charges are arranged on the corners of the polygon of n side

    long double theta;
    theta=0;
    for(int i=0; i<n; i++)
    {
        temp_q.pos.ztransform(theta);        //Transform the vector by theta angle keeping z coordinate constant

        theta=theta+2*(PI/n);               //Update the angle

        create_charge(temp_q);              //Creates a new nodal charge
    }
}

// Main program goes here

int main()
{   int n;
    charge temp_q;
    efield E;
    vect test;
    char ch;
    do
    {
        cout<<"How are the charges separated?"<<endl;
        cout<<"1. Corners of a regular polygon"<<endl;
        cout<<"2. I prefer to enter the position on my own >_<"<<endl;
        cout<<"Your choice: ";
        cin>>ch;

        if(ch=='1')
        {
            cout<<"Enter the number of sides: ";
            cin>>n;
            cout<<"Enter common charge: ";
            cin>>temp_q.q;

            cout<<"Enter positon of first charge: ";
            temp_q.pos.in_pos();
            poly_charge(n, temp_q);

            cout<<"Enter position of the test charge: ";
            test.in_pos();

            cout<<"Electric field is given as: ";

            E.field_calc(test, head);

            E.print();


        }

                                      //For custom charges
        else if(ch=='2')
        {
        }

    cout<<"Do you want to try again? (y/N)";
    cin>>ch;
    }while(ch=='y');

}
















