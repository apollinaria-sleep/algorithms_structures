#ifndef AVL_HEAD_H_2022_03_24
#define AVL_HEAD_H_2022_03_24

#include "mm.h"
#include "iostream"

namespace lab618 {

    template <class T, int(*Compare)(const T *pElement, const T* pElement2)>
    class CAVLTree {
    private:
        struct leaf {
            T* pData;
            leaf *pLeft;
            leaf *pRight;
            int balanceFactor; // h(R) - h(L)
        };

    public:
        class CException {
        public:
            CException() {
            }
        };

    public:
        CAVLTree(): m_pRoot(0), m_Memory(10, true){
        }

        virtual ~CAVLTree() {
            clear();
        }

        bool add(T* pElement) {
            if (!findLeaf(pElement)) {
                add_leaf(pElement, m_pRoot);
                return true;
            }

            return false;
        }

        bool update(T* pElement) {
            leaf* leaf_ = findLeaf(pElement);
            if (!leaf_) {
                add(pElement);
                return false;
            }

            leaf_->pData = pElement;
            return true;
        }
      
        T* find(const T& pElement) {
            leaf* leaf_ = findLeaf(&pElement);
            if (!leaf_) {
                return nullptr;
            }

            return leaf_->pData;
        }

        bool remove(const T& element) {
            bool find_leaf = false;
            remove_leaf(&element, m_pRoot, &find_leaf);
            return find_leaf;
        }

        void clear() {
            clear_leaf(m_pRoot);
            m_Memory.clear();
        }

    private:
        leaf* findLeaf(const T* pElement) {
            leaf* leaf_ = m_pRoot;
            while (leaf_) {
                int cmp = Compare(pElement, leaf_->pData);
                if (cmp > 0) {
                    leaf_ = leaf_->pRight;
                } else if (cmp < 0) {
                    leaf_ = leaf_->pLeft;
                } else {
                    return leaf_;
                }
            }
            return 0;
        }

        int max(const int& first, const int& second) {
            return (first >= second ? first : second);
        }

        int min(const int& first, const int& second) {
            return (first <= second ? first : second);
        }

        leaf* small_right_rotation(leaf* leaf_) {
            leaf* rotate_leaf = leaf_->pLeft;
            leaf_->pLeft = rotate_leaf->pRight;
            rotate_leaf->pRight = leaf_;

            if (rotate_leaf->balanceFactor > 0) {
                leaf_->balanceFactor++;
            } else {
                leaf_->balanceFactor = leaf_->balanceFactor - rotate_leaf->balanceFactor + 1;
            }
            rotate_leaf->balanceFactor = 1 + rotate_leaf->balanceFactor + max(0, leaf_->balanceFactor);
            return rotate_leaf;
        }

        leaf* small_left_rotation(leaf*& leaf_) {
            leaf* rotate_leaf = leaf_->pRight;
            leaf_->pRight = rotate_leaf->pLeft;
            rotate_leaf->pLeft = leaf_;

            if (rotate_leaf->balanceFactor > 0) {
                leaf_->balanceFactor = leaf_->balanceFactor - rotate_leaf->balanceFactor - 1;
            } else {
                leaf_->balanceFactor--;
            }
            rotate_leaf->balanceFactor = min(leaf_->balanceFactor, 0) + rotate_leaf->balanceFactor - 1;
            return rotate_leaf;
        }

        leaf* balance(leaf*& root) {
            if (!root) {
                return root;
            }
            if (root->balanceFactor == 2) { // h(R) - h(L) = 2 - правое дерево больше
                if (root->pRight->balanceFactor == -1) {
                    root->pRight = small_right_rotation(root->pRight);
                }
                return small_left_rotation(root);
            } else if (root->balanceFactor == -2) { // h(L) - h(R) = 2 - левое дерево больше
                if (root->pRight->balanceFactor == 1) {
                    root->pLeft = small_left_rotation(root->pLeft);
                }
                return small_right_rotation(root);
            }
            return root;
        }

        bool add_leaf(T* pElement, leaf*& root) {
            if (!root) {
                leaf* new_leaf = m_Memory.newObject();
                new_leaf->pData = pElement;
                new_leaf->pLeft = 0;
                new_leaf->pRight = 0;
                new_leaf->balanceFactor = 0;
                root = new_leaf;
                return true;
            }
            bool keep_moving;
            if (Compare(pElement, root->pData) > 0) {
                if (keep_moving = add_leaf(pElement, root->pRight)) {
                    root->balanceFactor++;
                }
            } else {
                if (keep_moving = add_leaf(pElement, root->pLeft)) {
                    root->balanceFactor--;
                }
            }
            root = balance(root);
            return keep_moving && root->balanceFactor != 0;
        }

        leaf* find_nearest(leaf* left, leaf* right, int balance) {
            leaf* root;
            if (balance > 0) {
                root = right;
                while (root->pLeft) {
                    root = root->pLeft;
                }
            } else {
                root = left;
                while (root->pRight) {
                    root = root->pRight;
                }
            }
            root->balanceFactor = balance;
            return root;
        }

        bool remove_nearest(leaf*& root, const int& ind_dir) {
            if (ind_dir == 1 && !root->pLeft) {
                root = root->pRight;
                return true;
            }
            if (ind_dir == 0 && !root->pRight) {
                root = root->pLeft;
                return true;
            }
            bool keep_moving;
            if (keep_moving = remove_nearest((ind_dir == 1 ? root->pLeft : root->pRight), ind_dir)) {
                root->balanceFactor += (ind_dir == 1 ? 1 : -1);
            }
            root = balance(root);
            return keep_moving && root->balanceFactor == 0;
        }

        bool remove_leaf(const T* pElement, leaf*& root, bool* find_leaf) {
            if (!root) {
                return false;
            }
            bool keep_moving;
            int cmp = Compare(pElement, root->pData);
            if (cmp > 0) {
                if (keep_moving = remove_leaf(pElement, root->pRight, find_leaf)) {
                    root->balanceFactor--;
                }
            } else if (cmp < 0) {
                if (keep_moving = remove_leaf(pElement, root->pLeft, find_leaf)) {
                    root->balanceFactor++;
                }
            } else { // нашли нужный элемент
                *find_leaf = true;
                leaf* right = root->pRight;
                leaf* left = root->pLeft;
                if (!left) {
                    m_Memory.deleteObject(root);
                    root = right;
                    return true;
                } else if (!root->pRight) {
                    m_Memory.deleteObject(root);
                    root = left;
                    return true;
                }
                leaf* nearest_leaf = find_nearest(left, right, root->balanceFactor);
                int ind_dir = (Compare(nearest_leaf->pData, root->pData) > 0 ? 1 : 0);
                m_Memory.deleteObject(root);
                root = nearest_leaf;
                if (keep_moving = remove_nearest((ind_dir == 1 ? right : left), ind_dir)) {
                    root->balanceFactor += (ind_dir == 1 ? -1 : 1);
                }
                root->pLeft = left;
                root->pRight = right;
            }
            root = balance(root);
            return keep_moving && root->balanceFactor == 0;
        }

        void clear_leaf(leaf*& root) {
            if (!root) {
                return;
            }
            clear_leaf(root->pLeft);
            clear_leaf(root->pRight);
            root = 0;
        }

        leaf* m_pRoot;
        CMemoryManager<leaf> m_Memory;
    };

}; // namespace templates

#endif // #define AVL_HEAD_H_2015_03_31
