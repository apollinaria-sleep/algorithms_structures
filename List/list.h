#ifndef TEMPLATES_LIST_2022_02_03
#define TEMPLATES_LIST_2022_02_03

namespace lab618 {
    template<class T>
    class CSingleLinkedList {
    private:
        struct leaf {
            T data;
            leaf* pnext;
            leaf(T& _data, leaf* _pnext) : data(_data), pnext(_pnext) {}
        };
    public:
        class CIterator {
        public:
            CIterator() : m_pCurrent(0), m_pBegin(0) {
            }

            CIterator(leaf *p) : m_pCurrent(p), m_pBegin(0) {
            }

            CIterator(const CIterator &src) : m_pCurrent(src.m_pCurrent), m_pBegin(src.m_pBegin) {
            }

            ~CIterator() {
                m_pCurrent = 0;
                m_pBegin = 0;
            }

            CIterator& operator=(const CIterator&  src) {
                m_pCurrent = src.m_pCurrent;
                m_pBegin = src.m_pBegin;
                return *this;
            }

            bool operator!=(const CIterator&  it) const {
                return m_pCurrent != it.m_pCurrent || m_pBegin != it.m_pBegin;
            }

            void operator++() {
                if (m_pBegin) {
                    m_pCurrent = m_pBegin;
                    m_pBegin = 0;
                } else {
                    m_pCurrent = m_pCurrent->pnext;
                }
            }

            T& getData() {
                return m_pCurrent->data;
            }

            T& operator*() {
                return m_pCurrent->data;
            }

            leaf* getLeaf() {
                return m_pCurrent;
            }

            void setLeaf(leaf* p) {
                m_pCurrent = p;
                m_pBegin = 0;
            }

            void setLeafPreBegin(leaf* p) {
                m_pCurrent = 0;
                m_pBegin = p;
            }

            bool isValid() {
                return m_pCurrent;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
        };

    public:

        CSingleLinkedList() : m_pBegin(0), m_pEnd(0){
        }

        virtual ~CSingleLinkedList() {
            clear();
        }

        void pushBack(T& data) {
            leaf* new_leaf = new leaf(data, 0);

            if (m_pBegin) {
                m_pEnd->pnext = new_leaf;
                m_pEnd = new_leaf;
            } else {
                m_pBegin = new_leaf;
                m_pEnd = new_leaf;
            }
        }

        void pushFront(T& data) {
            leaf* new_leaf = new leaf(data, 0);

            if (m_pBegin) {
                new_leaf->pnext = m_pBegin;
                m_pBegin = new_leaf;
            } else {
                m_pBegin = new_leaf;
                m_pEnd = new_leaf;
            }
        }

        T popFront() {
            if (m_pBegin == nullptr) {
                return T();
            }

            T tmp = m_pBegin->data;
            if (m_pBegin == m_pEnd) {
                m_pEnd = 0;
            }
            leaf* next_leaf = m_pBegin->pnext;
            delete m_pBegin;
            m_pBegin = next_leaf;

            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it) {
            if (!it.isValid()) {
                return;
            }

            leaf* leaf_ = it.getLeaf();
            if (leaf_ == m_pBegin) {
                m_pBegin = m_pBegin->pnext;
                it.setLeafPreBegin(leaf_->pnext);
            } else {
                leaf* prev = m_pBegin;
                while (prev->pnext != leaf_) {
                    prev = prev->pnext;
                }
                it.setLeaf(prev);
                prev->pnext = leaf_->pnext;
                if (!leaf_->pnext) {
                    m_pEnd = prev;
                }
            }
            delete leaf_;
        }

        int getSize() {
            if (!m_pBegin) {
                return 0;
            }

            int size = 1;
            leaf* tmp = m_pBegin;
            while (tmp->pnext) {
                tmp = tmp->pnext;
                size++;
            }
            return size;
        }

        void clear() {
            while (m_pBegin != m_pEnd) {
                leaf* next_leaf = m_pBegin->pnext;
                delete m_pBegin;
                m_pBegin = next_leaf;
            }
            m_pBegin = 0;
            m_pEnd = 0;
        }

        CIterator begin() {
            return CIterator(m_pBegin);
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };

    template<class T>
    class CDualLinkedList {
    private:
        struct leaf {
            T data;
            leaf * pnext, *pprev;
            leaf(T& _data, leaf * _pprev, leaf * _pnext) : data(_data), pprev(_pprev), pnext(_pnext) {
            }
        };
    public:
        class CIterator {
        public:
            CIterator() : m_pBegin(0), m_pCurrent(0), m_pEnd(0) {
            }

            CIterator(leaf *p) : m_pBegin(0), m_pCurrent(p), m_pEnd(0) {
            }

            CIterator(const CIterator &src)
                    : m_pBegin(src.m_pBegin), m_pCurrent(src.m_pCurrent), m_pEnd(src.m_pEnd) {
            }

            ~CIterator() {
                m_pBegin = 0;
                m_pCurrent = 0;
                m_pEnd = 0;
            }

            CIterator& operator = (const CIterator&  src) {
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
                m_pEnd = src.m_pEnd;
                return *this;
            }

            bool operator != (const CIterator&  it) const {
                return m_pBegin != it.m_pBegin || m_pCurrent != it.m_pCurrent || m_pEnd != it.m_pEnd;
            }

            void operator++() {
                if (m_pBegin) {
                    m_pCurrent = m_pBegin;
                    m_pBegin = 0;
                } else {
                    if (m_pCurrent) {
                        m_pCurrent = m_pCurrent->pnext;
                    }
                }
            }

            void operator--() {
                if (m_pEnd) {
                    m_pCurrent = m_pEnd;
                    m_pEnd = 0;
                } else {
                    if (m_pCurrent) {
                        m_pCurrent = m_pCurrent->pprev;
                    }
                }
            }

            T& getData() {
                return m_pCurrent->data;
            }

            T& operator* () {
                return m_pCurrent->data;
            }

            leaf* getLeaf() {
                return m_pCurrent;
            }

            // применяется в erase и eraseAndNext
            void setLeaf(leaf* p) {
                m_pBegin = 0;
                m_pCurrent = p;
                m_pEnd = 0;
            }

            // применяется в erase и eraseAndNext
            void setLeafPreBegin(leaf* p) {
                m_pBegin = p;
                m_pCurrent = 0;
                m_pEnd = 0;
            }

            // применяется в erase и eraseAndNext
            void setLeafPostEnd(leaf* p) {
                m_pBegin = 0;
                m_pCurrent = 0;
                m_pEnd = p;
            }

            bool isValid() {
                return m_pCurrent;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
            //храним конец списка, если мы находимся после конца
            leaf* m_pEnd;
        };

    public:

        CDualLinkedList() : m_pBegin(0), m_pEnd(0) {
        };

        virtual ~CDualLinkedList() {
            clear();
        };

        void pushBack(T& data) {
            leaf* new_leaf = new leaf(data, 0, 0);

            if (m_pBegin) {
                m_pEnd->pnext = new_leaf;
                new_leaf->pprev = m_pEnd;
                m_pEnd = new_leaf;
            } else {
                m_pBegin = new_leaf;
                m_pEnd = new_leaf;
            }
        }

        T popBack() {
            if (!m_pEnd) {
                return T();
            }

            T tmp = m_pEnd->data;
            leaf* prev_leaf = m_pEnd->pprev;
            if (!prev_leaf) {
                m_pBegin = 0;
            } else {
                prev_leaf->pnext = 0;
            }
            delete m_pEnd;
            m_pEnd = prev_leaf;

            return tmp;
        }

        void pushFront(T& data) {
            leaf* new_leaf = new leaf(data, 0, 0);

            if (m_pBegin) {
                new_leaf->pnext = m_pBegin;
                m_pBegin->pprev = new_leaf;
                m_pBegin = new_leaf;
            } else {
                m_pBegin = new_leaf;
                m_pEnd = new_leaf;
            }
        }

        T popFront() {
            if (!m_pBegin) {
                return T();
            }

            T tmp = m_pBegin->data;
            leaf* next_leaf = m_pBegin->pnext;
            if (!next_leaf) {
                m_pEnd = 0;
            } else {
                next_leaf->pprev = 0;
            }
            delete m_pBegin;
            m_pBegin = next_leaf;

            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it) {
            if (!it.isValid()) {
                return;
            }

            leaf* leaf_ = it.getLeaf();
            if (leaf_->pprev) {
                leaf_->pprev->pnext = leaf_->pnext;
                it.setLeaf(leaf_->pprev);
            } else {
                m_pBegin = leaf_->pnext;
                it.setLeafPreBegin(m_pBegin);
            }
            if (leaf_->pnext) {
                leaf_->pnext->pprev = leaf_->pprev;
            } else {
                m_pEnd = leaf_->pprev;
            }

            leaf_->pprev = 0;
            leaf_->pnext = 0;
            delete leaf_;
        }

        // изменяет состояние итератора. выставляет следующую позицию.
        void eraseAndNext(CIterator& it) {
            if (!it.isValid()) {
                return;
            }

            leaf* leaf_ = it.getLeaf();
            if (leaf_->pprev) {
                leaf_->pprev->pnext = leaf_->pnext;
            } else {
                m_pBegin = leaf_->pnext;
            }
            if (leaf_->pnext) {
                leaf_->pnext->pprev = leaf_->pprev;
                it.setLeaf(leaf_->pnext);
            } else {
                m_pEnd = leaf_->pprev;
                it.setLeafPostEnd(m_pEnd);
            }

            leaf_->pprev = 0;
            leaf_->pnext = 0;
            delete leaf_;
        }

        int getSize() {
            if (!m_pBegin) {
                return 0;
            }

            int size = 1;
            leaf* tmp = m_pBegin;
            while (tmp->pnext) {
                tmp = tmp->pnext;
                size++;
            }
            return size;
        }

        void clear() {
            while (m_pBegin != m_pEnd) {
                leaf* next_leaf = m_pBegin->pnext;
                delete m_pBegin;
                m_pBegin = next_leaf;
            }
            m_pBegin = 0;
            m_pEnd = 0;
        }

        CIterator begin() {
            return CIterator(m_pBegin);
        }

        CIterator end() {
            return CIterator(m_pEnd);
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };
};
#endif //#ifndef TEMPLATES_LIST_2022_02_03
