#ifndef TESTCLASS_H
#define TESTCLASS_H

class TestClass
{
    public:
        int num_text;

        TestClass();
        ~TestClass();
        void text_print(int &);



    private:
        unsigned int rand_num;
};

#endif//TESTCLASS_H_