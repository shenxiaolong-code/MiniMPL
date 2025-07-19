
command echo -e "# +++++++++ loading\e[0;34m ${BASH_SOURCE[0]}:${LINENO}  \e[0;0m" ;
echo
build_src_="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd -L)"
output_dir=${TEMP_DIR}/to_del/output/mlir-crtp-proposal

echo "make -C ${build_src_} output_dir=${output_dir}"
make -C ${build_src_} output_dir=${output_dir}   2>&1  | tee ${TEMP_DIR}/to_del/mlir-crtp-proposal.log

mv ${TEMP_DIR}/to_del/mlir-crtp-proposal.log ${output_dir}/

echo
command ls --color=always -1 -Artd ${output_dir}/*  | sort

# nm -s ${output_dir}/3_symbol_bloat_optimize_demo | grep  "dump.*_type_info" | sort -t'_' -k3
echo
command echo -e "# --------- leaving\e[0;34m ${BASH_SOURCE[0]}:${LINENO}  \e[0;0m"