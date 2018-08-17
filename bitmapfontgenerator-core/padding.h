#ifndef PADDING_H
#define PADDING_H


struct Padding
{
    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;

    Padding(){}
    Padding(int left, int top, int right, int bottom)
    {
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
    }
};

#endif // PADDING_H
