gtest         = dependency('gtest')
dependencies  = [gtest, mesh_dep]

elements  = executable('elements', 'elements.cpp', dependencies: dependencies)
nodes     = executable(   'nodes',    'nodes.cpp', dependencies: dependencies)
format    = executable(  'format',   'format.cpp', dependencies: dependencies)

test('elements', elements)
test(   'nodes',    nodes)
test(  'format',   format)
