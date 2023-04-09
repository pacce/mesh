gtest         = dependency('gtest')
dependencies  = [gtest, mesh_dep]

elements  = executable('elements', 'elements.cpp', dependencies: dependencies)
format    = executable(  'format',   'format.cpp', dependencies: dependencies)
mesh      = executable(    'mesh',     'mesh.cpp', dependencies: dependencies)
nodes     = executable(   'nodes',    'nodes.cpp', dependencies: dependencies)
physical  = executable('physical', 'physical.cpp', dependencies: dependencies)

test('elements', elements)
test(  'format',   format)
test(    'mesh',     mesh)
test(   'nodes',    nodes)
test('physical', physical)
