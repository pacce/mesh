gtest         = dependency('gtest')
dependencies  = [gtest, mesh_dep]

nodes   = executable( 'nodes',  'nodes.cpp', dependencies: dependencies)
format  = executable('format', 'format.cpp', dependencies: dependencies)

test( 'nodes',  nodes)
test('format', format)
