#include <iostream>
#include <deque>

using namespace std;

template <class _Ty, class _Container = deque<_Ty>>
struct queue {
	using value_type = typename _Container::value_type;
	using reference = typename _Container::reference;
	using const_reference = typename _Container::const_reference;
	using size_type = typename _Container::size_type;
	using container_type = _Container;

	queue() = default;

	explicit queue(const _Container& _Cont) : c(_Cont) {}

	explicit queue(_Container&& _Cont) noexcept(is_nothrow_move_constructible_v<_Container>) 
		: c(move(_Cont)) {}

	template<class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
	explicit queue(const _Alloc& _All) noexcept(is_nothrow_constructible_v<_Container,const _Alloc&>) 
		: c(_All) {}

	template<class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
	explicit queue(const _Container& _Cont,const _Alloc& _All ) : c(_Cont, _All) {}

	template<class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
	explicit queue(_Container&& _Cont, const _Alloc& _All) 
		noexcept(is_nothrow_constructible_v<_Container, _Container, const _Alloc&>) 
		: c(move(_Cont), _All) {}

	template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
	queue(const queue& _Right, const _Alloc& _Al) : c(_Right.c, _Al) {}

	template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
	queue(queue&& _Right, const _Alloc& _Al) noexcept(
		is_nothrow_constructible_v<_Container, _Container, const _Alloc&>)
		: c(move(_Right.c), _Al) {}

////////////////////////////////////////////////////////////////////////

	_NODISCARD_EMPTY_ADAPTOR_MEMBER bool empty() const noexcept(c.empty()){
		return c.empty();
	}

	_NODISCARD size_type size() const noexcept(noexcept(c.size())) {
		return c.size();
	}
	
	_NODISCARD reference front() noexcept(noexcept(c.front())) {
		return c.front();
	}

	_NODISCARD const_reference front() const noexcept(noexcept(c.front())) {
		return c.front();
	}

	_NODISCARD reference back() noexcept(noexcept(c.back())) {
		return c.back();
	}

	_NODISCARD const_reference back() const noexcept(noexcept(c.back())) {
		return c.back();
	}

	void push(const value_type& _Val) {
		c.push_back(_Val);
	}

	void push(value_type&& _Val) {
		c.push_back(move(_Val));
	}

	template<class... _Valty>
	decltype(auto) emplace(_Valty&&... _Val) {
		c.emplace_back(forward<_Valty>(_Val)...);
	}

	void pop() noexcept(noexcept(c.pop_front())) {
		c.pop_front();
	}

	void swap(queue& Right) noexcept(_Is_nothrow_swappable<_Container>::value) {
		_Swap_adl(c, Right.c);
	}

	_NODISCARD const _Container& _Get_Container() {
		return c;
	}

private:
	_Container c{};
};

struct Rectangle {
	Rectangle() = default;
	Rectangle(int x, int y) : x(x), y(y) {}

	friend ostream& operator<<(ostream& os, Rectangle _Rec) {
		os << _Rec.x << " " << _Rec.y;
		return os;
	}
private:
	int x;
	int y;
};

/// ////////////////////////////////////////////////////////////
template<class T, enable_if_t<is_integral_v<T>, int> = 0>
void Fun(T value) {
	cout << "int: " << value << endl;
}
/// /////////////////////////////////////////////////////////////

int main() {
	queue<Rectangle> Recs;

/////////////////////// Разница между push и emplace 
/////////////////////// push:

	Rectangle r(10, 20);
	Recs.push(r);
	cout << Recs.back() << endl;

/////////////////////// emplace:

	Recs.emplace(11, 22);
	cout << Recs.back() << endl;

/////////////////////// Проверка 

	const type_info& result = typeid(Recs.back());
	cout << result.name() << endl;

	return 0;
}