//! Src: https://stackoverflow.com/questions/18135593/function-templates-vs-auto-keyword

// FIXME: get thsi exmapel to work ...

void myFunction(auto &arg) {
  return arg + 2;
}

template <typename T>
void myFunction_1(T &arg)
{
    // ~
}


void myFunction_2(auto &arg)
{
    // ~
}
