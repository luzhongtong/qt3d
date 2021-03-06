TEMPLATE = subdirs

src_core.subdir = $$PWD/core
src_core.target = sub-core

src_render.subdir = $$PWD/render
src_render.target = sub-render
src_render.depends = src_core

src_bulletphysics.subdir = $$PWD/bulletphysics
src_bulletphysics.target = sub-bulletphysics
src_bulletphysics.depends = src_core

src_openal.subdir = $$PWD/openal
src_openal.target = sub-openal
src_openal.depends = src_core

src_input.subdir = $$PWD/input
src_input.target = sub-input
src_input.depends = src_render

# Quick3D libs
src_quick3d_core.subdir = $$PWD/quick3d/quick3d
src_quick3d_core.target = sub-quick3d-core
src_quick3d_core.depends = src_core src_input

src_quick3d_render.subdir = $$PWD/quick3d/quick3drenderer
src_quick3d_render.target = sub-quick3d-render
src_quick3d_render.depends = src_render src_quick3d_core


# Quick3D imports
src_quick3d_core_imports.file = $$PWD/quick3d/imports/core/importscore.pro
src_quick3d_core_imports.target = sub-quick3d-imports-core
src_quick3d_core_imports.depends = src_quick3d_core

src_quick3d_imports_render.file = $$PWD/quick3d/imports/render/importsrender.pro
src_quick3d_imports_render.target = sub-quick3d-imports-render
src_quick3d_imports_render.depends = src_quick3d_render

src_quick3d_imports_scene3d.file = $$PWD/quick3d/imports/scene3d/importsscene3d.pro
src_quick3d_imports_scene3d.target = sub-quick3d-imports-scene3d
src_quick3d_imports_scene3d.depends = src_quick3d_render src_input

src_quick3d_imports_bulletphysics.file = $$PWD/quick3d/imports/bulletphysics/importsbulletphysics.pro
src_quick3d_imports_bulletphysics.target = sub-quick3d-imports-bulletphysics
src_quick3d_imports_bulletphysics.depends = src_bulletphysics

src_quick3d_imports_input.file = $$PWD/quick3d/imports/input/importsinputs.pro
src_quick3d_imports_input.target = sub-quick3d-imports-input
src_quick3d_imports_input.depends = src_input

# Qt3D Scene Parser plugins
src_plugins_sceneparsers.file = $$PWD/plugins/sceneparsers/sceneparsers.pro
src_plugins_sceneparsers.target = sub-plugins-sceneparsers
src_plugins_sceneparsers.depends = src_render

SUBDIRS += \
    src_core \
    src_render \
    src_input \
    src_openal \
    src_quick3d_core \
    src_quick3d_core_imports \
    src_quick3d_render \
    src_quick3d_imports_render \
    src_quick3d_imports_scene3d \
    src_quick3d_imports_input \
    src_plugins_sceneparsers

config_bullet {
    SUBDIRS += \
        src_bulletphysics \
        src_quick3d_imports_bulletphysics
}


