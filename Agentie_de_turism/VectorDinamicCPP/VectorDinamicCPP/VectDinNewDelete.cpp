#include "VectDinNewDelete.h"


/*
Constructor default
Alocam loc pentru 5 elemente
*/
VectDinNewDelete::VectDinNewDelete() :elems{ new Element[INITIAL_CAPACITY] }, cap{ INITIAL_CAPACITY }, lg{ 0 } {}

/*
Constructor de copiere
Obiectul current (this) acum se creaza
aloca spatiu pentru elemente
copieaza elementele din ot in this
*/
VectDinNewDelete::VectDinNewDelete(const VectDinNewDelete& ot) {
	elems = new Element[ot.cap];
	//copiez elementele
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];  //assignment din Pet
	}
	lg = ot.lg;
	cap = ot.cap;
}

/*
Operator assgnment
elibereaza ce era in obiectul curent (this)
aloca spatiu pentru elemente
copieaza elementele din ot in this
*/
VectDinNewDelete& VectDinNewDelete::operator=(const VectDinNewDelete& ot) {
	if (this == &ot) {
		return *this;//s-a facut l=l;
	}
	delete[] elems;
	elems = new Element[ot.cap];
	//copiez elementele
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];  //assignment din Pet
	}
	lg = ot.lg;
	cap = ot.cap;
	return *this;
}

/*
Eliberam memoria
*/
VectDinNewDelete::~VectDinNewDelete() {
	delete[] elems;
}


/*
Move constructor
Apelat daca construim un nou vector dintr-un r-value (ex temporary)
Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
*/
VectDinNewDelete::VectDinNewDelete(VectDinNewDelete&& ot) {
	// Copy the data pointer from other
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	// Release the data pointer from the source object so that  
	// the destructor does not free the memory multiple times.  
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
}

/*
Move assignment
Similar cu move constructor
Folosit la assignment
Elibereaza ce continea obiectul curent (this)
"fura" interiorul lui ot
pregateste ot pentru distrugere
*/
VectDinNewDelete& VectDinNewDelete::operator=(VectDinNewDelete&& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	// Copy the data pointer from other
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	// Release the data pointer from the source object so that  
	// the destructor does not free the memory multiple times.  
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
	return *this;
}

void VectDinNewDelete::add(const Element& el) {
	ensureCapacity();//daca e nevoie mai alocam memorie
	elems[lg++] = el;
}

Element& VectDinNewDelete::get(int poz) const {
	return elems[poz];
}

void VectDinNewDelete::set(int poz, const Element& el) {
	elems[poz] = el;
}

int VectDinNewDelete::size() const noexcept {
	return lg;
}

void VectDinNewDelete::ensureCapacity() {
	if (lg < cap) {
		return; //mai avem loc
	}
	cap *= 2;
	Element* aux = new Element[cap];
	for (int i = 0; i < lg; i++) {
		aux[i] = elems[i];
	}
	delete[] elems;
	elems = aux;
}


IteratorVectorND VectDinNewDelete::begin()
{
	return IteratorVectorND(*this);
}

IteratorVectorND VectDinNewDelete::end()
{
	return IteratorVectorND(*this, lg);
}


IteratorVectorND::IteratorVectorND(const VectDinNewDelete& v) noexcept:v{ v } {}
IteratorVectorND::IteratorVectorND(const VectDinNewDelete& v, int poz)noexcept :v{ v }, poz{ poz } {}

bool IteratorVectorND::valid()const noexcept {
	return poz < v.lg;
}
Element& IteratorVectorND::element() const noexcept {
	return v.elems[poz];
}
void IteratorVectorND::next() noexcept {
	poz++;
}
Element& IteratorVectorND::operator*() {
	return element();
}
IteratorVectorND& IteratorVectorND::operator++() {
	next();
	return *this;
}
bool IteratorVectorND::operator==(const IteratorVectorND& ot) noexcept {
	return poz == ot.poz;
}
bool IteratorVectorND::operator!=(const IteratorVectorND& ot)noexcept {
	return !(*this == ot);
}
