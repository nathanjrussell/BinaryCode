#include "BinaryCodeWord.hpp"
#include "BinaryCodeGenMat.hpp"
#include "BinaryCode.hpp"
#include <iostream>



int main() {
    BinaryCodeWord r0(4), r1(4);
    r0.setBit(1,1); r0.setBit(3,1);
    r1.setBit(1,1); r1.setBit(2,1);
    BinaryCodeGenMat G({r0, r1});
    BinaryCode code(G);

    std::cout << "n = " << code.length() << ", k = " << code.dimension() << "\n";
    std::cout << "RREF rows:\n";
    for (int i = 0; i < code.rref().numRows(); ++i) std::cout<< code.rref()[i] << '\n';
    std::cout << "Systematic rows:\n";
    for (int i = 0; i < code.systematic().numRows(); ++i) std::cout << code.systematic()[i] << '\n';


    BinaryCodeGenMat EH(4, 8);
    for (int i = 0; i < 4; ++i) {
        EH.setEntry(i, i, 1);          // identity part
        for (int j = 0; j<4; j++)
        {
            EH.setEntry(i,4+j,i==j ? 0 : 1);
        }
    }
    std::cout << "EH matrix:\n" << EH << '\n';
    BinaryCode code2(EH);
    std::cout << "Code2 n = " << code2.length() << ", k = " << code2.dimension() << "\n";
    for (int wt = 0; wt <= 8; ++wt) {
        std::cout << "Weight " << wt << ": " << code2.get_weight_distribution(wt) << '\n';
    }

    BinaryCodeGenMat gen3(18,36);
    for (int i = 0; i < 18; ++i) {
        gen3.setEntry(i,i+18,1);
        for (int j = 0; j < 18; ++j) {
            gen3.setEntry(i, j, i==j ? 0 : 1);
        }
    }
    std::cout << "Gen3 matrix:\n" << gen3 << '\n';
    BinaryCode code3(gen3);
    std::cout<< "Gen3 Systematic:\n" << code3.systematic() << '\n';
    std::cout << "Code3 n = " << code3.length() << ", k = " << code3.dimension() << "\n";

    for (int wt = 0; wt <= 36; ++wt) {
        int count = code3.get_weight_distribution(wt);
        if (count > 0)
            std::cout << "Weight " << wt << ": " << count << '\n';
    }

    return 0;
}

