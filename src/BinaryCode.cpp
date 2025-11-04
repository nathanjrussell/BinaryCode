#include "BinaryCode.hpp"


static int find_pivot_row(const std::vector<BinaryCodeWord>& rows, int start_row, int col) {
    for (int r = start_row; r < (int)rows.size(); ++r) {
        if (rows[r].getBit(col)) return r;
    }
    return -1;
}

BinaryCode::BinaryCode(const BinaryCodeGenMat& G)
    : G_orig_(G),
      G_rref_(G),   // must initialize (no default ctor)
      G_sys_(G),    // must initialize (no default ctor)
      k_(0),
      n_(G.length())

{
    G_rref_ = compute_rref_no_col_swaps(G_orig_, k_);
    G_sys_  = compute_systematic_with_col_swaps(G_orig_, k_);

}

BinaryCodeGenMat BinaryCode::compute_rref_no_col_swaps(const BinaryCodeGenMat& G, int& out_rank) {
    std::vector<BinaryCodeWord> rows;
    rows.reserve(G.numRows());
    for (int i = 0; i < G.numRows(); ++i) rows.push_back(G[i]);

    const int n = G.length();
    const int k = (int)rows.size();

    int lead_row = 0;
    for (int col = 0; col < n && lead_row < k; ++col) {
        int piv = find_pivot_row(rows, lead_row, col);
        if (piv < 0) continue;
        if (piv != lead_row) std::swap(rows[piv], rows[lead_row]);
        // eliminate all other 1s in this column
        for (int r = 0; r < k; ++r) {
            if (r == lead_row) continue;
            if (rows[r].getBit(col)) rows[r] += rows[lead_row];
        }
        lead_row++;
    }

    out_rank = lead_row;
    std::vector<BinaryCodeWord> kept(rows.begin(), rows.begin() + out_rank);
    return BinaryCodeGenMat(kept);
}

void BinaryCode::swap_columns(std::vector<BinaryCodeWord>& rows, int a, int b) {
    if (a == b) return;
    for (auto& w : rows) {
        int ba = w.getBit(a);
        int bb = w.getBit(b);
        if (ba != bb) {
            w.setBit(a, bb);
            w.setBit(b, ba);
        }
    }
}

BinaryCodeGenMat BinaryCode::compute_systematic_with_col_swaps(const BinaryCodeGenMat& G, int rank) {
    std::vector<BinaryCodeWord> rows;
    rows.reserve(G.numRows());
    for (int i = 0; i < G.numRows(); ++i) rows.push_back(G[i]);

    const int n = G.length();
    const int k = (int)rows.size();

    int lead_row = 0;
    int col = 0;
    while (lead_row < rank && col < n) {
        int piv = find_pivot_row(rows, lead_row, col);
        if (piv < 0) {
            // try to source a pivot from a later column via column swap
            int c2 = col + 1;
            bool swapped = false;
            while (c2 < n) {
                int r = find_pivot_row(rows, lead_row, c2);
                if (r >= 0) {
                    swap_columns(rows, col, c2);
                    piv = r;
                    swapped = true;   // (fixed)
                    break;
                }
                ++c2;
            }
            if (!swapped) { ++col; continue; }
        }
        if (piv != lead_row) std::swap(rows[piv], rows[lead_row]);
        // clear other rows in this pivot column
        for (int r = 0; r < k; ++r) {
            if (r == lead_row) continue;
            if (rows[r].getBit(col)) rows[r] += rows[lead_row];
        }
        lead_row++;
        col++;
    }

    std::vector<BinaryCodeWord> kept(rows.begin(), rows.begin() + rank);
    return BinaryCodeGenMat(kept);
}

void BinaryCode::compute_weight_distribution()
{
    // To be implemented: compute weight distribution of the code
    if (wt_dist_) return; // already computed
    wt_dist_ = new int[n_ + 1];
    for (int i=0; i<=n_; ++i) wt_dist_[i] = 0;
    int max_weight = 0;
    int min_weight = n_;
    for (int i=0; i<1<<k_; ++i)
    {
        BinaryCodeWord unencoded(k_);
        for (int j=0; j<k_; ++j)
        {
            if (i & (1<<j))
                unencoded.setBit(j, 1);
        }
        int wt = (unencoded * G_sys_).weight();
        if (wt > max_weight) { max_weight = wt; }
        if (wt > 0 && wt < min_weight) { min_weight = wt; }
        wt_dist_[wt]++;
    }
    min_wt_ = min_weight;
    max_wt_ = max_weight;
}


int BinaryCode::min_wt() {
    if (min_wt_ == 0) compute_weight_distribution();
    return min_wt_;
}

int BinaryCode::get_weight_distribution(int weight) {
    if (wt_dist_ == nullptr) compute_weight_distribution();
    if (weight < 0 || weight > n_) return 0;
    return wt_dist_[weight];
}

std::vector<int> BinaryCode::get_weight_distribution() {
    std::vector<int> dist;
    if (wt_dist_ == nullptr) compute_weight_distribution();
    for (int i=0; i<=n_; ++i)
    {
        dist.push_back(wt_dist_[i]);
    }
    return dist;
}