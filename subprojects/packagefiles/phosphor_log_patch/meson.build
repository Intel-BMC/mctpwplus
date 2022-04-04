project('phosphor-logging', 'cpp',
  meson_version : '>=0.56.0',
)

cpp = meson.get_compiler('cpp')

incdir = include_directories('.')
if not cpp.has_header('phosphor-logging/log.hpp', include_directories: incdir)
  r=run_command('bootstrap.sh')
  output = r.stdout().strip()
  message(output)
  r2=run_command('configure')
  output = r2.stdout().strip()
  message(output)
endif

# Currently header-only libs are enough
#
# If building dependency is necessary Meson has experimental support for 
# Autotools projects.
# https://mesonbuild.com/External-Project-module.html
phosphorlog_dep = declare_dependency(include_directories: incdir)

meson.override_dependency('phosphor-logging', phosphorlog_dep)
