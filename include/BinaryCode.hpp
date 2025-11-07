#ifndef BINARY_CODE_HPP
#define BINARY_CODE_HPP

#include <vector>
#include <stdexcept>
#include <set>
#include "BinaryCodeWord.hpp"
#include "BinaryCodeGenMat.hpp"

class BinaryCode {
public:
    explicit BinaryCode(const BinaryCodeGenMat& G);

    int dimension() const { return k_; }
    int length() const { return n_; }

    const BinaryCodeGenMat& original()  const { return G_orig_; }
    const BinaryCodeGenMat& rref()      const { return G_rref_; }
    const BinaryCodeGenMat& systematic()const { return G_sys_;  }
    int get_weight_distribution(int weight);
    std::vector<int> get_weight_distribution();
    unsigned long long get_automorphism_group_size();
    void compute_automorphism_group();

private:
    static BinaryCodeGenMat compute_rref_no_col_swaps(const BinaryCodeGenMat& G, int& out_rank);
    static BinaryCodeGenMat compute_systematic_with_col_swaps(const BinaryCodeGenMat& G, int rank);
    void compute_weight_distribution();
    void identify_column_permutation_candidates();
    int min_wt();
    static void swap_columns(std::vector<BinaryCodeWord>& rows, int a, int b);

private:
    BinaryCodeGenMat G_orig_;
    BinaryCodeGenMat G_rref_;
    BinaryCodeGenMat G_sys_;
    int *wt_dist_;
    int **col_counts_by_wt_;
    std::vector<std::set<int>> perm_candidates_sets_;
    int k_ = 0;
    int n_ = 0;
    int max_wt_ = 0;
    int min_wt_ = 0;
    unsigned long long automorphism_group_size_ = 0;
};

#endif // BINARY_CODE_HPP
