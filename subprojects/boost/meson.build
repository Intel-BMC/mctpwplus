
project('boost', 'cpp',
         version: '1.75',
         meson_version: '>=0.56.0')

cxx = meson.get_compiler('cpp')
fs = import('fs')
# Build if not available
build_dir = join_paths(meson.current_source_dir(), 'build')
r = run_command('[','!','-d', build_dir, ']', check: true)
if r.returncode() == 0

      message('Boost libs not found. Downloading boost using wget')
      tar_download = run_command('wget', '-nc', '--no-check-certificate', 'https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz', check: true)
      message('Download complete. Extracting')
      assert(fs.exists('boost_1_76_0.tar.gz'), 'Boost download failed')
      extract_cmd = run_command('tar', '-xf', 'boost_1_76_0.tar.gz', '--strip-components', '1', check: true)
      message('Extracted boost source files. Running bootstarp.sh')

      r = run_command('./bootstrap.sh', '--with-libraries=coroutine,system', check: false)
      assert(r.returncode() == 0,
            'Bootstrap failed' +
            '\nstdout: ' + r.stdout().strip() +
            '\nstderr: ' + r.stderr().strip())

      r = run_command('./b2', 'install','--prefix=build', check: false)
      assert(r.returncode() == 0,
            'b2 failed' +
            '\nstdout: ' + r.stdout().strip() +
            '\nstderr: ' + r.stderr().strip())
      message('Boost setup succesful')
endif

include_dir = join_paths('build', 'include')
lib_dir = join_paths(meson.current_source_dir(), 'build', 'lib')

custom_dep = declare_dependency(link_args: ['-L' + lib_dir,
					    '-Wl,-rpath-link,' + lib_dir
					   ])

boost_inc = include_directories(include_dir, is_system:true)
boost_dep = declare_dependency(
       include_directories : boost_inc,
       dependencies : [cxx.find_library('boost_context', dirs: lib_dir, static: true),
                       cxx.find_library('boost_thread', dirs: lib_dir, static: true),
                       cxx.find_library('boost_coroutine', dirs: lib_dir, static: true),
                       custom_dep])

meson.override_dependency('boost', boost_dep)
