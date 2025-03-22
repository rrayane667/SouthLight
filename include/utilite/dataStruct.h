#pragma once
#include <stdlib.h> 
#include <iostream>
#include <string>
#include <tuple>
namespace DATASTRUCT {

	template <typename T>
	struct List{
		
		virtual T* begin()=0;
		virtual T* end()=0;
		List(List<T>* l){copy(l);};
		List() {};
		virtual ~List() = default;
		virtual void append(const T& el) = 0;
		virtual void remove(int index) = 0;
		virtual void insert(int index, T& el) = 0;
		virtual int capacity() = 0;
		virtual int len() = 0;
		virtual T pop() = 0;
		virtual T& get(int index) = 0;
		virtual T& operator[](int index) = 0;
		virtual void aff(std::ostream& where) const= 0;
		virtual void reserve(int new_maximun_size) = 0;

		List<T>& operator=( List<T>& l) {return *copy(l);}

		friend std::ostream& operator<<(std::ostream& o, const List<T>& l) {l.aff(o);
																	  return o;};
		virtual void swap(int ind1, int ind2) = 0;
		private:
		virtual List<T>* copy( List<T>& l) = 0;

	};

	template <typename T, typename U>
	class paire : public std::pair<T, U> {
	public:

		using std::pair<T, U>::pair; 
	
		friend std::ostream& operator<<(std::ostream& o, const paire<T, U>& p) {
			o << "(" << p.first << ", " << p.second << ")";
			return o;
		}
	};

	template <typename T>
	class Trio : public std::tuple<T, T, T> {
	public:

		Trio(T x, T y, T z) : std::tuple<T, T, T>(x, y, z) {}
	
		friend std::ostream& operator<<(std::ostream& o, const Trio<T>& t) {
			o << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ")";
			return o;
		}
	
		T operator[](int index) const {
			switch(index) {
				case 0: return std::get<0>(*this);
				case 1: return std::get<1>(*this);
				case 2: return std::get<2>(*this);
				default: throw std::out_of_range("Invalid Trio index");
			}
		}
	};

	template <typename T>
	class SparseSet {
		List<int> *sparse;
		List<T> *dense;
		int lastDenseIndex = -1;
		void setSparseLen(int len);
		public:
			inline T* begin(){return dense->begin();}
			inline T* end(){return dense->end();}
			SparseSet();
			~SparseSet();
			void set(int index_sparse,const T& el) ;
			void remove(int index_sparse) ;
			
			SparseSet( const SparseSet<T>& s){
				sparse = new DynamicList<int>(s.sparse);
				dense = new DynamicList<T>(s.dense);
			}

			SparseSet<T>& operator=(const SparseSet<T>& s) {
				*sparse = *s.sparse;
				*dense = *s.dense; 
				return *this;
			}

			inline int getIndex(int index){ return index<sparse->len()?(*sparse)[index]:-1;}

			inline T& operator[](int index) {
				if ((*sparse)[index] == -1 || index > (*sparse).len()) {
					throw std::out_of_range("SparseSet::operator[]: ID not in set");
				}
				return (*dense)[(*sparse)[index]];
			}
			void aff(std::ostream& o)  const{
				o << "Sparse set : "<< std::endl;
				o << "Sparse : ";
				sparse->aff(o);
				o << "Dense : ";
				dense->aff(o);
			}

			friend std::ostream& operator<<(std::ostream& o, const SparseSet<T>& s){
				s.aff(o);
				return o;
			}

			
	};
	

	template <typename T>
	class DynamicList : public List<T>{
		T* liste;
		int max_size;
		int current_index;
		inline bool isFull(){return max_size == current_index + 1;}
		inline bool isEmpty(){return -1 == current_index;}
		
		inline int getMaxLen(){return max_size-1;}

		//copy content of l
		List<T>* copy( List<T>& l) override ;

		public:
			
			
			DynamicList(DynamicList<T>* l){copy(*l);};
			DynamicList<T>& operator=(const DynamicList<T>& dl);

			inline T* begin() override { return liste; } 
			inline T* end() override { return liste + current_index + 1; }
			void swap(int ind1, int ind2) override;
			DynamicList();
			~DynamicList() override;
			void append(const T& el) override;
			void remove(int index) override;
			void insert(int index, T& el) override;
			int capacity() override{return max_size;}
			void reserve(int new_maximun_size) override;
			inline int len() override{return current_index+1;}
			T pop() override;
			
			inline T& operator[](int index) override{//checker si index existe????
				return get(index);
			}
			T& get(int index) override {
				if(index<= current_index)
				return liste[index];
				else {throw std::runtime_error("DynamicList out of bounds");}
			}
			void aff(std::ostream& where) const override {
				where << "Dynamic list : [" ;
				for(int i =0; i<=current_index; i++){
					
					where << liste[i] << ", ";
				}
				where << "]" ;
			}
	};

	template <typename T>
	class Stack : public DynamicList<T>{
		public:
			void remove(int index) = delete;
			void insert(int index, T& el) = delete;
			T& operator[](int) = delete;

	};
}

#include "dataStruct.tpp"