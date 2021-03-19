echo 'Compiling code...'
make

echo '\n'

echo '## KNAPSACK BRANCH AND BOUND SOLUTION ##'
./kp_bab tests/f1_l-d_kp_10_269
./kp_bab tests/f2_l-d_kp_20_878
./kp_bab tests/f3_l-d_kp_4_20
./kp_bab tests/f4_l-d_kp_4_11
./kp_bab tests/f5_l-d_kp_15_375
./kp_bab tests/f6_l-d_kp_10_60
./kp_bab tests/f7_l-d_kp_7_50
./kp_bab tests/f8_l-d_kp_23_10000
./kp_bab tests/f9_l-d_kp_5_80
./kp_bab tests/f10_l-d_kp_20_879

echo '\n'

echo '## KNAPSACK BACKTRACKING SOLUTION ##'
./kp_back tests/f1_l-d_kp_10_269
./kp_back tests/f2_l-d_kp_20_878
./kp_back tests/f3_l-d_kp_4_20
./kp_back tests/f4_l-d_kp_4_11
./kp_back tests/f5_l-d_kp_15_375
./kp_back tests/f6_l-d_kp_10_60
./kp_back tests/f7_l-d_kp_7_50
./kp_back tests/f8_l-d_kp_23_10000
./kp_back tests/f9_l-d_kp_5_80
./kp_back tests/f10_l-d_kp_20_879