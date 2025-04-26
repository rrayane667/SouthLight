#include "dataStruct.h"
#include<iostream>
#include "json/json.hpp"

using json = nlohmann::json;
namespace DATASTRUCT{


	template <typename T>
	void to_json(json& j, const List<T>& l) {
		j = json::array();
		for (auto& x: l) {
			j.push_back(l);
		}
	}
	template <typename T>
	void from_json(const json& j, List<T>& l) {
    for (std::size_t i = 0; i < j.size(); ++i) {
        l.append(j.at(i).get<T>());
    }
}


	
	template <typename T>
	DynamicList<T>::DynamicList() : max_size(8), current_index(-1){
		liste = (T*) ::operator new[](max_size * sizeof(T));
	}
	
	template <typename T>
	List<T>* DynamicList<T>::copy(List<T>& l) {
		
		if(&l==this){return this;}
		DynamicList<T>* dl = dynamic_cast<DynamicList<T>*>(&l);
		max_size = dl->max_size;
		current_index = dl->current_index;
		liste = static_cast<T*>(::operator new[](max_size * sizeof(T)));
		
		for (int i = 0; i <= current_index; i++) {
			new (liste + i) T(dl->liste[i]);
		}
		return this;
	}

	template <typename T>
	DynamicList<T>& DynamicList<T>::operator=(const DynamicList<T>& dl){
		if(dl.liste==(*this).liste){return *this;}
		if constexpr (std::is_pointer_v<T>) {
	
			for (int i = 0; i <= current_index; i++) {
				delete liste[i];
			}
		}
		else{

			for (int i = 0; i <= current_index; i++) {
				(liste + i)->~T();
			}
		}
		::operator delete[] (liste);
		max_size = dl.max_size;
		current_index = dl.current_index;
		liste = (T*) ::operator new[](max_size * sizeof(T)); 

		for(int i = 0; i<=current_index; i++){
			new (liste+i) T(dl.liste[i]);
		}
		return *this;
	}

	template <typename T>
	DynamicList<T>::~DynamicList() {
		if constexpr (std::is_pointer_v<T>) {
            
            for (int i = 0; i <= current_index; i++) {
                delete liste[i];
            }
		}
		else{

			for (int i = 0; i <= current_index; i++) {
				(liste + i)->~T();
			}
		}

		

		::operator delete[](liste);

		liste = nullptr;         
		current_index = -1;      
		max_size = 0;            
	}


	template <typename T>
	void DynamicList<T>::reserve(int new_capacity) {

		if (new_capacity <= max_size) {
			return;
		}

		T* new_liste = static_cast<T*>(::operator new[](new_capacity * sizeof(T)));


		for (int i = 0; i <= current_index; i++) {
			new (new_liste + i) T(liste[i]); 
		}

		for (int i = 0; i <= current_index; i++) {
			(liste + i)->~T();
		}

		::operator delete[](liste);

		liste = new_liste;
		max_size = new_capacity;
	}


	template <typename T>
	void DynamicList<T>::append(const T& el){
		if( isFull() ){

			reserve(max_size+8);
		}

		current_index++;
		new (liste+current_index) T(el);
		
	}

	template <typename T>
	void DynamicList<T>::swap(int ind1, int ind2) {
		if (ind1 == ind2) return;
	
		T temp = liste[ind1];
		liste[ind1] = liste[ind2];
		liste[ind2] = temp;
	}
	

	template <typename T>
	void DynamicList<T>::remove(int index) {
		
		if (index > (current_index)) {
			return;
		}
		
		if (index == (current_index)) {
			current_index--;
			return;
		}
	
		swap(index, current_index);
		(liste + current_index)->~T();
		current_index--;
	}

	template <typename T>
	T DynamicList<T>::pop(){

		if(isEmpty()){throw std::out_of_range("Cannot pop from an empty list");}

		current_index--;

		return liste[current_index+1];
		
	}


	template <typename T>
	void DynamicList<T>::insert(int a, T& b){
		//a ajouter
	}


	template <typename T>
	SparseSet<T>::SparseSet(){
		sparse = new DynamicList<int>();
		dense = new DynamicList<T>();

		for(int i = 0; i < 8; i++){
			sparse->append(-1);
		}
	}
	template <typename T>
	void SparseSet<T>::set(int index_sparse,const T& el){
		
		if (getIndex(index_sparse) != -1) {(*dense)[getIndex(index_sparse)]=el; return;}
		dense->append(el);
		lastDenseIndex = index_sparse;

		setSparseLen(index_sparse+1);
		
		(*sparse)[index_sparse] = dense->len()-1;
	}

	template <typename T>
	void SparseSet<T>::remove(int index_sparse){//FAUX??
		// Check if there is a valid mapping at index_sparse.
		if (index_sparse >= sparse->len() || (*sparse)[index_sparse] == -1)
        return;

		// Get the dense index for the element to remove.
		int denseIndexToRemove = (*sparse)[index_sparse];
		// Determine the dense index of the last element.
		int lastDenseIndex = dense->len() - 1;

		// Swap the element to remove with the last element in dense.
		dense->swap(denseIndexToRemove, lastDenseIndex);

		// Now we must update the sparse mapping for the element that was moved.
		// Iterate over the sparse list to find the entry that pointed to the last element.
		for (int i = 0; i < sparse->len(); ++i) {
			if ((*sparse)[i] == lastDenseIndex) {
				(*sparse)[i] = denseIndexToRemove;
				break;
			}
		}

		// Remove the last element from the dense list.
		dense->pop();

		// Mark the removed entity's sparse slot as empty.
		(*sparse)[index_sparse] = -1;

	}

	inline int indexMax(List<int> *l){
		if(l->len() == 0)
        {throw std::runtime_error("cant remove a zbi");;} // or handle the error appropriately

		int m = -1;
		// First, search for an initial valid index.
		for(int i = 0; i < l->len(); i++){
			if((*l)[i] != -1){
				m = i;
				break;
			}
		}
		// If no valid mapping was found, return -1.
		if(m == -1)
			return -1;
		
		// Now, search for the maximum among valid entries.
		for(int i = 0; i < l->len(); i++){
			if((*l)[i] != -1 && (*l)[i] > (*l)[m]){
				m = i;
			}
		}
		return m;
	}

	template <typename T>
	SparseSet<T>::~SparseSet() {
    	delete sparse;  
    	delete dense;
	}

	template <typename T>
	void SparseSet<T>::setSparseLen(int len){

		if(len < sparse->len()){return;}

		sparse->reserve(len);
		while (sparse->len() < len) {
			sparse->append(-1);
		}
	}

	template <typename T>
	Queue<T>::Queue(){
		queue = new DynamicList<T>();
	}

	template <typename T>
	void Queue<T>::append(T element){
		queue.append(element);
	}

	template <typename T>
	T Queue<T>::get(){
		return queue->get(0);
	}

}
