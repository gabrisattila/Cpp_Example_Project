#ifndef PIPE_H
#define PIPE_H

#include <iostream>
#include <algorithm>
#include <functional>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

template<class T>
class Pipe{
    private:
        
        typedef std::vector<T (*)(T)> V;
        V v;

    public:

        void add_operation(T (*f)(T)){
            v.push_back(f);
        }

        T run(T pm){

            if (v.empty()) {
                return pm;
            }
            /*for (typename std::vector<T(*)(T)>::iterator i = v.begin();
                i != v.end(); i++) {
                T(*result)(T) = *i;
                pm = (*result)(pm);
            }*/
            for (int i = 0; i < v.size(); i++) {
                T(*result)(T) = v[i];
                pm = (*result)(pm);
            }

            return pm;
        }

        void clear(){
            v.clear();
        }

        template<class T2>
        Pipe<T>& operator+=(Pipe<T2> pm){

            /*for (typename std::vector<T2 (*)(T2)>::iterator i = pm.v.begin();
                i != pm.v.end(); i++) {
                this->v.push_back(*i);
            }*/
            for(int i=0; i<pm.v.size(); i++){
                v.push_back(pm.v[i]);
                //this->add_operation(pm.v[i]);
            }          
            return *this;
        }

        

        Pipe<T>& operator|(Pipe<T> pm) {

            /*for (typename std::vector<T (*)(T)>::iterator i = pm.v.begin();
                i != pm.v.end(); i++) {
                this->v.push_back(*i);
            }*/

            for (int i = 0; i < pm.v.size(); i++) {
                v.push_back(pm.v[i]);
                //this->add_operation(pm.v[i]);
            }
            return *this;
        }



        Pipe<T>& operator|(T(*f)(T)) {
            v.push_back(f);
            //this->add_operation(f);
            return *this;
        }

        template<class T2>
        T operator()(T2 pm){
                T result;
                if(v.empty()){
                    return pm;
                }else{
                    result = v[0](pm);
                    
                    /*for (typename std::vector<T(*)(T)>::iterator i = v.begin();
                        i != v.end(); i++) {
                        result = (*i)(result);
                    }*/

                    for(int i = 1; i<v.size(); i++){
                        result = v[i](result);
                    }
                }
                return result;
        }

        template<class T2>
        bool operator!=(T2 pm){
            T result;
            if(v.empty()){
                return pm;
            }else{
                result = v[0](pm);
                /*for (typename std::vector<T(*)(T)>::iterator i = v.begin();
                    i != v.end(); i++) {
                    result = (*i)(result);
                }*/
                for(int i = 1; i<v.size(); i++){
                    result = v[i](result);
                }
            }
            if(result == pm){
                return true;
            }else {
            return false;
            }
        }
        
        Pipe<T>() {}

        Pipe<T>(T (*f)(T)){
            this->add_operation(f);
        }
        template<class T2>
        Pipe<T> operator=(T2 (*f)(T2)){
            Pipe<T>();
            this->add_operation(f);
        }       
        
        template<class T2>
        Pipe<T> operator=(Pipe<T2> pm) {
            
            /*for (typename std::vector<T2(*)(T2)>::iterator i = pm.v.begin();
                i != pm.v.end(); i++)
            {
                this->v.push_back(*i);
            }*/
            for (int i = 0; i < pm.v.size(); i++) {
                this->v.push_back(pm.v[i]);
            }
        }

};

#endif // PIPE_H
