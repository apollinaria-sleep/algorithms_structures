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
                m_pCurrent = nullptr;
                m_pBegin = nullptr;
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
                if (m_pBegin != nullptr) {
                    m_pCurrent = m_pBegin;
                    m_pBegin = nullptr;
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
                m_pBegin = nullptr;
            }

            void setLeafPreBegin(leaf* p) {
                m_pCurrent = nullptr;
                m_pBegin = p;
            }

            bool isValid() {
                return m_pCurrent != nullptr;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
        };

    public:

        CSingleLinkedList() : m_pBegin(nullptr), m_pEnd(nullptr){
        }

        virtual ~CSingleLinkedList() {
            clear();
        }

        void pushBack(T& data) {
            leaf* new_leaf = new leaf(data, nullptr);
            if (m_pBegin != nullptr) {
                m_pEnd->pnext = new_leaf;
                m_pEnd = new_leaf;
            } else {
                m_pBegin = new_leaf;
                m_pEnd = new_leaf;
            }
        }

        void pushFront(T& data) {
            leaf* new_leaf = new leaf(data, nullptr);

            if (m_pBegin != nullptr) {
                new_leaf->pnext = m_pBegin;
                m_pBegin = new_leaf;
            } else {
                m_pBegin = new_leaf;
                m_pEnd = new_leaf;
            }
        }

        T popFront() {
            T tmp = m_pBegin->data;

            if (m_pBegin == nullptr) {
                throw "List is empty\n";
            }
            if (m_pBegin == m_pEnd) {
                m_pEnd = nullptr;
            }

            leaf* next_leaf = m_pBegin->pnext;
            delete m_pBegin;
            m_pBegin = next_leaf;

            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it) {
  
        }

        int getSize() {
            if (m_pBegin == nullptr) {
                return 0;
            }

            int size = 1;
            leaf* tmp = m_pBegin;
            while (tmp->pnext != nullptr) {
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
            m_pBegin = nullptr;
            m_pEnd = nullptr;
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
            leaf(T& _data, leaf * _pprev, leaf * _pnext) {
            }
        };
    public:
        class CIterator {
        public:
            CIterator() {
            }

            CIterator(leaf *p) {
            }

            CIterator(const CIterator &src) {
            }

            ~CIterator() {
            }

            CIterator& operator = (const CIterator&  src) {
            }

            bool operator != (const CIterator&  it) const {
            }

            void operator++() {
            }

            void operator--() {
            }

            T& getData() {
                T tmp;
                return tmp;
            }

            T& operator* () {
                T tmp;
                return tmp;
            }

            leaf* getLeaf() {
                return 0;
            }

            // применяется в erase и eraseAndNext
            void setLeaf(leaf* p) {
            }

            // применяется в erase и eraseAndNext
            void setLeafPreBegin(leaf* p) {
            }

            // применяется в erase и eraseAndNext
            void setLeafPostEnd(leaf* p) {
            }

            bool isValid() {
                return false;
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

        CDualLinkedList() {
        };

        virtual ~CDualLinkedList() {
        };

        void pushBack(T& data) {
        }

        T popBack() {
            T tmp;
            return tmp;
        }

        void pushFront(T& data) {
        }

        T popFront() {
            T tmp;
            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it) {
        }

        // изменяет состояние итератора. выставляет следующую позицию.
        void eraseAndNext(CIterator& it) {
        }

        int getSize() {
            return 0;
        }

        void clear() {
        }

        CIterator begin() {
            return CIterator();
        }

        CIterator end() {
            return CIterator();
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };
};
#endif //#ifndef TEMPLATES_LIST_2022_02_03
