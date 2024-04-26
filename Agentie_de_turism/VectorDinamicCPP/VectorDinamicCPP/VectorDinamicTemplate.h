#ifndef MYVECTOR_H_
#define MYVECTOR_H_

template <typename TElem>
class IteratorVector;

template <typename TElem>
class VectorDinamic {
private:

	TElem* elemente; // vectorul
	int Size;
	int capacitate;
	void redimensionare();

public:

	//Constructor.
	VectorDinamic();

	//Destructor.
	~VectorDinamic();

	//Constructor de copiere.
	VectorDinamic(const VectorDinamic& ot);


	//Operatorul de asignare.
	VectorDinamic& operator=(const VectorDinamic& ot);

	//Adaugare in vector.
	void add(const TElem& el);

	TElem& get(int poz) const;

	int size() const noexcept;

	bool empty() const noexcept;

	void erase(int poz);

	friend class IteratorVector<TElem>;

	IteratorVector<TElem> begin() const;

	IteratorVector<TElem> end() const;

	IteratorVector<TElem> iterator() {
		return IteratorVector(*this);
	}
};

template <typename TElem>
VectorDinamic<TElem>::VectorDinamic() : Size(0), capacitate(2) {
	this->elemente = new TElem[2];
}

template <typename TElem>
VectorDinamic<TElem>::~VectorDinamic() {
	delete[] elemente;
	Size = 0;
	capacitate = 0;
}

template <typename TElem>
VectorDinamic<TElem>::VectorDinamic(const VectorDinamic& ot) {
	this->elemente = new TElem[ot.capacitate];
	for (int i = 0; i < ot.Size; i++) {
		this->elemente[i] = ot.elemente[i];
	}
	this->Size = ot.Size;
	this->capacitate = ot.capacitate;
}

template <typename TElem>
void VectorDinamic<TElem>::erase(int poz) {
	this->Size--;
	for (int i = poz; i < this->Size; i++) {
		this->elemente[i] = this->elemente[i + 1];
	}
}

template <typename TElem>
void VectorDinamic<TElem>::redimensionare() {
	capacitate *= 2;
	auto* nou = new TElem[capacitate];
	for (int i = 0; i < Size; i++) {
		nou[i] = elemente[i];
	}
	delete[] elemente;
	elemente = nou;
}

template <typename TElem>
void VectorDinamic<TElem>::add(const TElem& e) {
	if (Size == capacitate) {
		redimensionare();
	}
	elemente[Size++] = e;
}

template<typename TElem>
VectorDinamic<TElem>& VectorDinamic<TElem>::operator=(const VectorDinamic<TElem>& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elemente;
	elemente = new TElem[ot.capacitate];
	for (int i = 0; i < ot.Size; i++) {
		elemente[i] = ot.elemente[i];
	}
	Size = ot.Size;
	capacitate = ot.capacitate;
	return *this;
}

template <typename TElem>
TElem& VectorDinamic<TElem>::get(int poz) const {
	return elemente[poz];
}

template <typename TElem>
int VectorDinamic<TElem>::size() const noexcept {
	return Size;
}

template <typename TElem>
bool VectorDinamic<TElem>::empty() const noexcept {
	return Size == 0;
}

template <typename TElem>
IteratorVector<TElem> VectorDinamic<TElem>::begin() const {
	return IteratorVector<TElem>(*this);
}

template <typename TElem>
IteratorVector<TElem> VectorDinamic<TElem>::end() const {
	return IteratorVector<TElem>(*this, Size);
}

template <typename TElem>
class IteratorVector {
private:

	const VectorDinamic<TElem>& vector; // referinta la vectorul dinamic
	int poz = 0; //Setam prima pozitie la 0.

public:

	explicit IteratorVector(const VectorDinamic<TElem>& v);
	IteratorVector(const VectorDinamic<TElem>& v, int poz) noexcept;

	bool valid() const;
	TElem& element() const;
	void next();
	TElem& operator*();
	IteratorVector& operator++();
	bool operator==(const IteratorVector& ot) noexcept;
	bool operator!=(const IteratorVector& ot) noexcept;
};

template <typename TElem>
IteratorVector<TElem>::IteratorVector(const VectorDinamic<TElem>& v) : vector(v) {}

template <typename TElem>
IteratorVector<TElem>::IteratorVector(const VectorDinamic<TElem>& v, int poz) noexcept : vector{ v }, poz{ poz } {}

template <typename TElem>
bool IteratorVector<TElem>::valid() const {
	return poz < vector.getSize();
}

template <typename TElem>
TElem& IteratorVector<TElem>::element() const {
	return vector.elemente[poz];
}

template <typename TElem>
void IteratorVector<TElem>::next() {
	poz++;
}

template <typename TElem>
TElem& IteratorVector<TElem>::operator*() {
	return element();
}

template <typename TElem>
IteratorVector<TElem>& IteratorVector<TElem>::operator++() {
	next();
	return *this;
}

template <typename TElem>
bool IteratorVector<TElem>::operator==(const IteratorVector<TElem>& ot) noexcept {
	return ot.poz == poz;
}

template <typename TElem>
bool IteratorVector<TElem>::operator!=(const IteratorVector<TElem>& ot) noexcept {
	return !(*this == ot);
}

#endif // !MYVECOTR_H_
