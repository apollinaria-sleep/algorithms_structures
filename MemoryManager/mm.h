#ifndef MEMORY_MANAGER_HEAD_H_2022_02_17
#define MEMORY_MANAGER_HEAD_H_2022_02_17

#include <iostream>

namespace lab618 {
    template <class T>
    class CMemoryManager {
    private:
        struct block {
            // Массив данных блока
            T* pdata;
            // Адрес следующего блока
            block *pnext;
            // Первая свободная ячейка
            int firstFreeIndex;
            // Число заполненных ячеек
            int usedCount;
        };
    public:
        class CException {
        public:
            CException() {}
        };

    public:
        CMemoryManager(int _default_block_size, bool isDeleteElementsOnDestruct = false)
            : m_blkSize(_default_block_size), m_pBlocks(0), m_pCurrentBlk(0),
            m_isDeleteElementsOnDestruct(isDeleteElementsOnDestruct) {}

        virtual ~CMemoryManager() {
            clear();
        }

        // Получить адрес нового элемента из менеджера
        T* newObject() {
            if (!m_pBlocks) { // если не было выделено ни одного блока памяти до сих пор
                m_pBlocks = newBlock();
                m_pCurrentBlk = m_pBlocks;
            }

            if (m_pCurrentBlk->usedCount == m_blkSize) { // хотим найти свободное место в других блоках
                 m_pCurrentBlk = m_pBlocks;
                 while (m_pCurrentBlk->pnext && m_pCurrentBlk->usedCount == m_blkSize) {
                     m_pCurrentBlk = m_pCurrentBlk->pnext;
                 }
                 if (m_pCurrentBlk->usedCount == m_blkSize) { // если все блоки памяти полностью заполнены
                     block* new_block = newBlock();
                     m_pCurrentBlk->pnext = new_block;
                     m_pCurrentBlk = new_block;
                 }
            }

            T* p = m_pCurrentBlk->pdata + m_pCurrentBlk->firstFreeIndex;
            int* index = reinterpret_cast<int*>(p);
            m_pCurrentBlk->firstFreeIndex = *index;
            new (reinterpret_cast<void*>(p)) T; // здесь будем вызывать конструктор объекта без выделения памяти
                                                // с помощью placement new
            m_pCurrentBlk->usedCount += 1;

            return p;
        }

        // Освободить элемент в менеджере
        bool deleteObject(T* p) {
            block* tmp = m_pBlocks;
            while (tmp) {
                int index = p - tmp->pdata;
                if (0 <= index && index < m_blkSize) {
                    p->~T();
                    tmp->usedCount -= 1;
                    int* p_index = reinterpret_cast<int*>(p);
                    *p_index = tmp->firstFreeIndex;
                    tmp->firstFreeIndex = index;
                    return true;
                }
                tmp = tmp->pnext;
            }
            return false;
        }

        // Очистка данных, зависит от m_isDeleteElementsOnDestruct
        void clear() {
            if (!m_pBlocks) {
                return;
            }

            block* tmp = m_pBlocks;
            while (tmp) {
                block* next = tmp->pnext;
                if (tmp->usedCount != 0) {
                    if (!m_isDeleteElementsOnDestruct) {
                        throw CException();
                    } else {
                        deleteBlock(tmp);
                    }
                }
                tmp = next;
            }

            m_pBlocks = 0;
            m_pCurrentBlk = 0;
        }
    private:

        // Создать новый блок данных. Применяется в newObject
        block* newBlock() {
            //T* newData = new T[m_blkSize]; - здесь происходит вызов конструкторов для Т, но затем мы 'сводим на нет'
                                            // работу конструктора тем, что заполняем память местами,
                                            // поэтому будем выделять память иначе, без вызова конструктора здесь
            T* newData = reinterpret_cast<T*>(new char[m_blkSize * sizeof(T)]);
            auto* newBlock = new block();
            newBlock->pdata = newData;
            for (int i = 1; i <= m_blkSize; i++) {
                int* index = reinterpret_cast<int*>(newData + (i - 1));
                if (i != m_blkSize) {
                    *index = i;
                } else {
                    *index = -1;
                }
            }
            newBlock->pnext = 0;
            newBlock->firstFreeIndex = 0;
            newBlock->usedCount = 0;

            return newBlock;
        }

        // Освободить память блока данных. Применяется в clear
        void deleteBlock(block *p) {
            delete[] reinterpret_cast<char*>(p->pdata);
            delete p;
        }

        // Размер блока
        int m_blkSize;
        // Начало списка блоков
        block* m_pBlocks;
        // Текущий блок
        block* m_pCurrentBlk;
        // Удалять ли элементы при освобождении
        bool m_isDeleteElementsOnDestruct;
    };
}; // namespace lab618

#endif // #define MEMORY_MANAGER_HEAD_H_2022_02_17
