////////////////////////////////////////////////////////////////////////////////
//
//	CHashTable.h (last update: Jan 31, 2005)
//


#ifndef __CHASHTABLE_H__
#define __CHASHTABLE_H__

#include "CList.h"

//略記用マクロ
#define _TEMPLATE   template <class T_Key, class T_Item >
#define _HASH       CHashTable<T_Key, T_Item >
#define _ENTRY      CHashEntry<T_Key, T_Item >
#define _LIST       CList<_ENTRY >
#define _LISTNODE   CListNode<_ENTRY >
#define KEY         const T_Key&
#define ITEM        const T_Item&


_TEMPLATE class CHashEntry;
_TEMPLATE class CHashTable {
public:

	//construction
	CHashTable();
	CHashTable(const _HASH&);
	CHashTable(int (*)(KEY), int nSize =37);

	//destruction
	virtual ~CHashTable();
	virtual void Delete();

	//initialization
	bool    Create(int (*)(KEY), int nSize =37);

	//member access (getting)
	int   (*Hash() const)(KEY);
	int     Size() const;
	int     Count() const;
	bool    IsEmpty() const;

	//operator
	_HASH&  operator = (const _HASH&);

	//operation
	bool    Get(T_Item*, KEY) const;
	T_Item  Get(KEY) const;
	bool    Put(KEY, ITEM);
	bool    Remove(KEY);
	bool    Pop(T_Item*, KEY);
	T_Item  Pop(KEY);
	bool    List(CList<_ENTRY*>*);
	bool    List(CList<const _ENTRY*>*) const;

protected:

	//destruction
	void    Destroy();

	//operation
	T_Item* Retrieve(KEY) const;

	int   (*m_pfnHash)(KEY);
	int     m_nSize;
	_LIST*  m_lpaList;
	int     m_nCount;

};


/* construction ------------------------------------------------------------- */

//コンストラクタ
_TEMPLATE inline CHashTable<T_Key, T_Item >::CHashTable()
: m_pfnHash(NULL), m_nSize(0), m_lpaList(NULL), m_nCount(0) {
}

//コンストラクタ
_TEMPLATE CHashTable<T_Key, T_Item >::CHashTable(const _HASH& h){

	if (h.m_pfnHash){

		int nSize =h.m_nSize;

		_LIST* lpaList =new _LIST [nSize];
		assert(lpaList);

		int i;
		for (i=0; i<nSize; ++i) lpaList[i] =h.m_lpaList[i];

		m_pfnHash =h.m_pfnHash;
		m_nSize   =nSize;
		m_lpaList =lpaList;
		m_nCount  =h.m_nCount;
	}
	else {
		m_pfnHash =NULL;
		m_nSize   =0;
		m_lpaList =NULL;
		m_nCount  =0;
	}

	return;
}

//コンストラクタ
_TEMPLATE CHashTable<T_Key, T_Item >::CHashTable(int (*pfnHash)(const T_Key&), int nSize){
	assert(pfnHash && nSize > 0);

	_LIST* lpaList =new _LIST [nSize];
	assert(pfnHash);

	m_pfnHash =pfnHash;
	m_nSize   =nSize;
	m_lpaList =lpaList;
	m_nCount  =0;
}


/* destruction -------------------------------------------------------------- */

//デストラクタ
_TEMPLATE CHashTable<T_Key, T_Item >::~CHashTable(){
	Destroy();
}

//オブジェクトの削除
_TEMPLATE void CHashTable<T_Key, T_Item >::Delete(){

	Destroy();

	m_pfnHash =NULL;
	m_nSize   =0;
	m_lpaList =NULL;
	m_nCount  =0;

	return;
}

//オブジェクトの破棄 [for internal use]
_TEMPLATE void CHashTable<T_Key, T_Item >::Destroy(){

	delete [] m_lpaList;

	return;
}


/* initialization ----------------------------------------------------------- */

//作成
_TEMPLATE bool CHashTable<T_Key, T_Item >::Create(int (*pfnHash)(KEY), int nSize){

	if (!pfnHash || nSize <= 0) return false;

	if (m_lpaList) return false;

	_LIST* lpaList =new _LIST [nSize];
	assert(lpaList);

	m_pfnHash =pfnHash;
	m_nSize   =nSize;
	m_lpaList =lpaList;
    m_nCount  =0;

	return true;
}


/* member access (getting) -------------------------------------------------- */

//ハッシュ関数の取得
_TEMPLATE inline int (* CHashTable<T_Key, T_Item>::Hash() const)(KEY){
	return m_pfnHash;
}

//ハッシュサイズの取得
_TEMPLATE inline int CHashTable<T_Key, T_Item>::Size() const {
	return m_nSize;
}

//要素数の取得
_TEMPLATE inline int CHashTable<T_Key, T_Item>::Count() const {
	return m_nCount;
}

//テーブルの空判定
_TEMPLATE inline bool CHashTable<T_Key, T_Item>::IsEmpty() const {
	return !m_nCount;
}


/* operator ----------------------------------------------------------------- */

//代入
_TEMPLATE _HASH& CHashTable<T_Key, T_Item >::operator = (const _HASH& h){

	Destroy();

	if (h.m_pfnHash){

		int nSize =h.m_nSize;

		_LIST* lpaList =new _LIST [nSize];
		assert(lpaList);

		int i;
		for (i=0; i<nSize; ++i) lpaList[i] =h.m_lpaList[i];

		m_pfnHash =h.m_pfnHash;
		m_nSize   =nSize;
		m_lpaList =lpaList;
		m_nCount  =h.m_nCount;
	}
	else {
		m_pfnHash =NULL;
		m_nSize   =0;
		m_lpaList =NULL;
		m_nCount  =0;
	}

	return *this;
}


/* operation ---------------------------------------------------------------- */

//アイテムの取得 (1)
_TEMPLATE T_Item CHashTable<T_Key, T_Item >::Get(KEY key) const {

	T_Item* lpItem =Retrieve(key);

	return (lpItem) ? *lpItem : T_Item(0);
}

//アイテムの取得 (2)
_TEMPLATE bool CHashTable<T_Key, T_Item >::Get(T_Item* lpRes, KEY key) const {

	T_Item* lpItem =Retrieve(key);
	if (!lpItem) return false;

	if (lpRes) *lpRes =*lpItem;

	return true;
}

//アイテムの検索 [for internal use]
_TEMPLATE T_Item* CHashTable<T_Key, T_Item >::Retrieve(KEY key) const {

	int nHash =(*m_pfnHash)(key);
	if (nHash < 0) return NULL;

	nHash %= m_nSize;

	_LISTNODE* p =m_lpaList[nHash];
	while (p){

		_ENTRY& entry =p->Item();

		if (entry.m_key == key) return &entry.m_item;

		p =p->Next();
	}

	return NULL;
}

//エントリの追加
_TEMPLATE bool CHashTable<T_Key, T_Item >::Put(KEY key, ITEM item){

	int nHash =(*m_pfnHash)(key);
	if (nHash < 0) return false;

	nHash %=m_nSize;

	//----------------------------------------------------------

	_LIST& list =m_lpaList[nHash];

	CListNode<_ENTRY >* p =list;
	while (p){

		_ENTRY& entry =p->Item();

		if (entry.m_key == key){

			list.RemoveNode(p);
			list.Append(_ENTRY(key, item));

			return true;
		}
	
		p =p->Next();
	}

	list.Append(_ENTRY(key, item));
	++m_nCount;

	return true;
}

//エントリの削除
_TEMPLATE bool CHashTable<T_Key, T_Item >::Remove(KEY key){

	if (!m_pfnHash) return false;



	int nHash =(*m_pfnHash)(key);
	if (nHash < 0) return false;

	nHash %=m_nSize;

	//----------------------------------------------------------

	_LIST& list =m_lpaList[nHash];

	CListNode<_ENTRY >* p =list;
	while (p){

		_ENTRY& entry =p->Item();

		if (entry.m_key == key){

			list.RemoveNode(p);
			--m_nCount;

			return true;
		}
	
		p =p->Next();
	}

	return false;
}

//ポップ (1)
_TEMPLATE bool CHashTable<T_Key, T_Item >::Pop(T_Item* lpRes, KEY key){

	if (!m_pfnHash) return false;

	int nHash =(*m_pfnHash)(key);
	if (nHash < 0) return false;

	nHash %=m_nSize;

	//----------------------------------------------------------

	_LIST& list =m_lpaList[nHash];

	CListNode<_ENTRY >* p =list;
	while (p){

		_ENTRY& entry =p->Item();

		if (entry.m_key == key){

			if (lpRes) *lpRes =entry.m_item;

			list.RemoveNode(p);
			--m_nCount;

			return true;
		}
	
		p =p->Next();
	}

	return false;
}

//ポップ (2)
_TEMPLATE T_Item CHashTable<T_Key, T_Item >::Pop(KEY key){

	if (!m_pfnHash) return false;

	int nHash =(*m_pfnHash)(key);
	if (nHash < 0) return false;

	nHash %=m_nSize;

	//----------------------------------------------------------

	_LIST& list =m_lpaList[nHash];

	CListNode<_ENTRY >* p =list;
	while (p){

		_ENTRY& entry =p->Item();

		if (entry.m_key == key){

			const T_Item res(entry.m_item);

			list.RemoveNode(p);
			--m_nCount;

			return res;
		}
	
		p =p->Next();
	}

	return T_Item(0);
}



//エントリの列挙
_TEMPLATE bool CHashTable<T_Key, T_Item >::List(CList<_ENTRY*>* lpList){

	if (!lpList) return false;

	lpList->Delete();

	int n =m_nSize;

	int i;
	for (i=0; i<n; ++i){

		CListNode<_ENTRY >* p =m_lpaList[i];

		while (p){
			lpList->Append(&p->Item());
			p =p->Next();
		}
	}

	return true;
}

//エントリの列挙 (const)
_TEMPLATE bool CHashTable<T_Key, T_Item >::List(CList<const _ENTRY*>* lpList) const {

	if (!lpList) return false;

	lpList->Delete();

	int n =m_nSize;

	int i;
	for (i=0; i<n; ++i){

		CListNode<_ENTRY >* p =m_lpaList[i];

		while (p){
			lpList->Append(&p->Item());
			p =p->Next();
		}
	}

	return true;
}


////////////////////////////////////////////////////////////////////////////////
//CHashEntry<T_Key, T_Item>

_TEMPLATE class CHashEntry {
	friend CHashTable<T_Key, T_Item >;
public:

	//construction
	CHashEntry(const _ENTRY&);
	CHashEntry(KEY, ITEM);

	//member access (reference)
	KEY     Key() const;
	T_Item& Item();
	ITEM    Item() const;

private:

	T_Key   m_key;
	T_Item  m_item;

};


/* construction ------------------------------------------------------------- */

//コンストラクタ
_TEMPLATE inline CHashEntry<T_Key, T_Item >::CHashEntry(const _ENTRY& entry)
: m_key(entry.m_key), m_item(entry.m_item) {
}

//コンストラクタ
_TEMPLATE inline CHashEntry<T_Key, T_Item >::CHashEntry(KEY key, ITEM item)
: m_key(key), m_item(item) {
}


/* member access (getting) -------------------------------------------------- */

//キーの参照 (const)
_TEMPLATE inline KEY CHashEntry<T_Key, T_Item >::Key() const {
	return m_key;
}

//アイテムの参照
_TEMPLATE inline T_Item& CHashEntry<T_Key, T_Item >::Item(){
	return m_item;
}

//アイテムの参照 (const)
_TEMPLATE inline ITEM CHashEntry<T_Key, T_Item >::Item() const {
	return m_item;
}


//略記用マクロ解除
#undef _TEMPLATE
#undef _HASH
#undef _ENTRY
#undef _LIST
#undef _LISTNODE
#undef KEY
#undef ITEM

#endif //__CHASHTABLE_H__
//[EOF]
