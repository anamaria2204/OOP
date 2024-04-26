#pragma once

#include "Pet.h"
typedef Pet Element;
#define INITIAL_CAPACITY 5


class IteratorVectorND;

class VectDinNewDelete
{
public:
	/*
	Constructor default
	Alocam loc pentru 5 elemente
	*/
	VectDinNewDelete();

	/*
	Constructor de copiere
	*/
	VectDinNewDelete(const VectDinNewDelete& ot); //rule of 3

	/*
	Eliberam memoria
	*/
	~VectDinNewDelete();//rule of 3

	/*
	  Operator assgnment
	  elibereaza ce era in obiectul curent (this)
	  aloca spatiu pentru elemente
	  copieaza elementele din ot in this
	*/
	VectDinNewDelete& operator=(const VectDinNewDelete& ot);//rule of 3


	/*
	 Move constructor
	 Apelat daca construim un nou vector dintr-un r-value (ex temporary, expresie de la return)
	 Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
	*/
	VectDinNewDelete(VectDinNewDelete&& ot); //rule of 5 

	/*
	Move assignment
	Similar cu move constructor
	Folosit la assignment 
	*/
	VectDinNewDelete& operator=(VectDinNewDelete&& ot); //rule of 5 


	void add(const Element& el);

	Element& get(int poz) const;

	void set(int poz, const Element& el);

	int size() const noexcept;

	friend class IteratorVectorND;
	//functii care creaza iteratori
	IteratorVectorND begin();
	IteratorVectorND end();


private:
	int lg;//numar elemente
	int cap;//capacitate
	Element* elems;//elemente

	void ensureCapacity();
};

class IteratorVectorND {
private:
	const VectDinNewDelete& v;
	int poz = 0;
public:
	IteratorVectorND(const VectDinNewDelete& v) noexcept;
	IteratorVectorND(const VectDinNewDelete& v, int poz)noexcept;
	bool valid()const noexcept;
	Element& element() const noexcept;
	void next() noexcept;
	Element& operator*();
	IteratorVectorND& operator++();
	bool operator==(const IteratorVectorND& ot)noexcept;
	bool operator!=(const IteratorVectorND& ot)noexcept;
};

