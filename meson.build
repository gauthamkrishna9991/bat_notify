project(
  'bat_notify',
  'c',
  version : '1.0',
  default_options : [
    'warning_level=3',
    'default_library=static',
  ]
)

bat_deps = [
  dependency('libnotify')
]

exe = executable(
  'bat_notify',
  'bat_notify.c',
  dependencies: bat_deps,
  install : true
)
