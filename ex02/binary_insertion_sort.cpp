
template <typename Container>
int PmergeMe<Container>::Jacobsthal(int k) {
    // Computes the k-th Jacobsthal number using the formula: J(k) = (2^(k+1) + (-1)^k) / 3.
    // Jacobsthal numbers are used to determine the indices for processing elements in a specific order
    // during the insertion phase of the sorting algorithm. The Jacobsthal sequence helps optimize the binary search 
    // during insertion by providing an efficient order for inserting elements.
    return round((pow(2, k + 1) + pow(-1, k)) / 3);
}

template <typename Container>
void PmergeMe<Container>::insert(Container &main, Container &pend, ValueType odd, Container &left, Container &vec, bool is_odd, int order) {
    // Inserts elements from the 'pend' container into the 'main' container in sorted order.
    // This method handles the merging process described in the article, where pairs from 'pend' are inserted
    // into 'main' using a binary search optimized by the Jacobsthal sequence.

    Iterator end;

    // If 'pend' has only one element, sort using normal binary search.
    if (pend.size() == 1) {
        end = std::upper_bound(main.begin(), main.end(), *pend.begin());
        main.insert(end, *pend.begin());
    } else if (pend.size() > 1) {
        // Process 'pend' using the Jacobsthal sequence to determine insertion indices.
        size_t jc = 3; // Start with the 3rd Jacobsthal number
        size_t count = 0;
        size_t idx;
        size_t decrease;
        
        // Sort 'pend' into 'main' using binary search 'upper_bound' with Jacobsthal as optimization.
        while (!pend.empty()) {
            idx = Jacobsthal(jc) - Jacobsthal(jc - 1);
            if (idx > pend.size())
                idx = pend.size();

            decrease = 0;
            while (idx) {
                // Determine the insertion point based on the Jacobsthal index and insert the element.
                end = main.begin();
                if (Jacobsthal(jc + count) - decrease <= main.size())
                    end = main.begin() + Jacobsthal(jc + count) - decrease;
                else
                    end = main.end();
                // Binary sort 
                end = std::upper_bound(main.begin(), end, *(pend.begin() + idx - 1));
                main.insert(end, *(pend.begin() + idx - 1));
                pend.erase(pend.begin() + idx - 1);

                idx--;
                decrease++;
                count++;
            }
            jc++;
        }
    }

    Container yaslam;
    
    // If there is an odd element, sort it using normal binary search.
    if (is_odd) {
        end = std::upper_bound(main.begin(), main.end(), odd);
        main.insert(end, odd);
    }
    // Rebuild 'main' based on the sorted last elements.
    for (Iterator i = main.begin(); i != main.end(); i++) {
        Iterator it = std::find(vec.begin(), vec.end(), *i);
        yaslam.insert(yaslam.end(), it - (order - 1), it + 1);
    }
    yaslam.insert(yaslam.end(), left.begin(), left.end());
    vec = yaslam;
}