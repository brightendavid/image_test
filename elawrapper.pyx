cdef extern from "ela.hpp":

    void processImage(int, void*)
    void new_func (char* filename)


def processImagepy():

  processImage(0,NULL)



def new_funcpy(filename):

  new_func(filename)


 
