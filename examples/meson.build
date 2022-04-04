cli11_dep = dependency('CLI11')

deps_no_thread += cli11_dep
deps_no_thread += mctpwplus_nothread_dep

ex_src_files = ['wrapper_object.cpp']
ex_wrapper_object = executable('wrapper_object', ex_src_files, dependencies: deps_no_thread)
