#ifndef SHARED_LIB_CLASS_H_INCLUDED
#define SHARED_LIB_CLASS_H_INCLUDED

#include <core/shared_lib.h>
#include <core/shared_lib_class.h>
#include <functional>

// the macro that creates two base classes (one in current and one in current::implementation)
//
// that current one manages the loading, copying and deleting of shared lib objects for your class
// + forwards function calls to the shared lib object which has the type implementation::_class_name_
//
// so the class in implementation gives an api to the class in the current namespace with functions to forward function calls to
// the functions are virtual, so that they can be implemented in the shared lib, by a class which inherits the implementation class
//
// create_class_name_, copy_class_name_ and delete_class_name_ need to be loaded from the shared lib in order for the class to work
//
// copy_class_name_ copies the object pointed to by the second param into the memory pointed to by the first param
// so the first param has to be already pointing to an object loaded from the shared lib
#define SHARED_LIB_DECL_BASE_CLASS(_class_name_, _class_name_Base, create_class_name_, copy_class_name_, delete_class_name_)                               \
                                                                                                                                                            \
        namespace implementation{ class _class_name_; }                                                                                                    \
                                                                                                                                                            \
                                                                                                                                                            \
        /** the functions that are going to be loaded from the shared library */                                                                            \
        extern std::function<implementation::_class_name_*(void)> create_class_name_;                                                                       \
        extern std::function<void(implementation::_class_name_*)> delete_class_name_;                                                                      \
        extern std::function<void(implementation::_class_name_*, implementation::_class_name_*)> copy_class_name_;                                          \
                                                                                                                                                            \
        typedef core::SharedLibClass<implementation::_class_name_, &create_class_name_, &copy_class_name_, &delete_class_name_> _class_name_Base;            \
        namespace implementation{ typedef core::EmptySharedLibClass _class_name_Base; }                                                                      \
                                                                                                                                                            \




// this macro needs to be put in the implementing .cpp file of the _class_name
// it defines the previously declared functions that need to be loaded from the shared lib
#define SHARED_LIB_DEF_BASE_CLASS(_class_name_, create_class_name_, copy_class_name, delete_class_name_)    \
                                                                                                            \
        std::function<implementation::_class_name_*()> create_class_name_;                                  \
        std::function<void(implementation::_class_name_*,implementation::_class_name_*)> copy_class_name;    \
        std::function<void(implementation::_class_name_*)> delete_class_name_;






namespace undicht {

    namespace core {


        template <typename T, std::function<T*()>* create, std::function<void(T*,T*)>* copy, std::function<void(T*)>* destroy>
        class SharedLibClass {
            /** a class that can handle an object loaded from a shared lib
            * (create it in the constructor, delete in destructor, copy in operator=, ...*/
            public:

                T* m_shared_lib_object = 0;


                SharedLibClass() {

                    m_shared_lib_object = (*create)();
                }

                SharedLibClass(const SharedLibClass& original){

                    // reserving enough memory before copying into it
                    m_shared_lib_object = (*create)();

                    *this = original; // should call the operator =
                }

                void operator= (const SharedLibClass& original){

                    (*copy)(m_shared_lib_object, original.m_shared_lib_object);
                }

                virtual ~SharedLibClass() {

                    (*destroy)(m_shared_lib_object);
                }

        };


        // used in the implementation namespace as the class the implementation class can inherit
        // since it has to inherit from the _class_name_Base,
        // because it shares the same declaration as the class which implements SharedLibClass<_class_name_> through _class_name_Base
        class EmptySharedLibClass {
            public:
                // the one that does nothing :D
        };


    } // core


} // undicht


#endif // SHARED_LIB_CLASS_H_INCLUDED
