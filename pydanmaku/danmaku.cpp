#include <Python.h>
#include <stdbool.h>
#include <math.h>
#include <list>
#include <iostream>
#include "bullet.h"
#include "renderer.h"

void deleteBullets(PyObject* capsule){
    std::list<Bullet> *bullets = (std::list<Bullet> *)PyCapsule_GetPointer(capsule, "bullet_list");
    bullets->clear();
}

static PyObject* DanmakuGroup_init(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    static std::list<Bullet> bullet_list;
    PyObject* list_pointer = PyCapsule_New(&bullet_list, "bullet_list", NULL);
    PyObject_SetAttrString(self, "bullet_list", list_pointer);
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_del(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "bullet_list");
    std::list<Bullet> *bullets = (std::list<Bullet> *)PyCapsule_GetPointer(capsule, "bullet_list");
    bullets->clear();
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_run(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "bullet_list");
    std::list<Bullet> to_remove;
    std::list<Bullet> *bullets = (std::list<Bullet> *)PyCapsule_GetPointer(capsule, "bullet_list");
    std::list<Bullet>::iterator b = bullets->begin();
    while (b != bullets->end()){
        if((*b).run(1.0f)){
            bullets->erase(b++);
        } else {
            b++;
        }
    }
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_render(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "bullet_list");
    std::list<Bullet> *bullets = (std::list<Bullet> *)PyCapsule_GetPointer(capsule, "bullet_list");
    render_bullets(bullets);
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_add(PyObject *self, PyObject *args){
    float x=0.0f;
    float y=0.0f;
    int is_rect=false;
    float height=0.0f, width=0.0f, radius=0.0f;
    float angle=0.0f, speed=0.0f;
    float acceleration=0.0f, angular_momentum=0.0f;
    if (!PyArg_ParseTuple(
        args, "Offpf|fffff",
        &self, &x, &y, &is_rect, &height, &width,
        &angle, &speed,
        &acceleration, &angular_momentum
    )) {return NULL;}
    if(is_rect && width == 0.0f){
        width = height;
    }else if(!is_rect){
        radius = width;
    }

    PyObject* capsule = PyObject_GetAttrString(self, "bullet_list");
    std::list<Bullet> *bullets = (std::list<Bullet> *)PyCapsule_GetPointer(capsule, "bullet_list");
    static Bullet bullet;
    if(is_rect){
        bullet = Bullet(x, y, width, height, speed, angle, acceleration, angular_momentum);
    } else {
        bullet = Bullet(x, y, radius, speed, angle, acceleration, angular_momentum);
    }
    bullets->emplace_front(bullet);
    Py_RETURN_NONE;
}

static PyObject* Danmaku_init(PyObject *self, PyObject *args){
    renderer_init();
    Py_RETURN_NONE;
}

static PyObject* Danmaku_close(PyObject *self, PyObject *args){
    renderer_close();
    Py_RETURN_NONE;
}

static PyMethodDef DanmakuGroupMethods[] =
{
    {"__init__", DanmakuGroup_init, METH_VARARGS, ""},
    {"__del__", DanmakuGroup_del, METH_VARARGS, ""},
    {"run", DanmakuGroup_run, METH_VARARGS, ""},
    {"render", DanmakuGroup_render, METH_VARARGS, ""},
    {"add_bullet", DanmakuGroup_add, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}  ,
};

static PyMethodDef ModuleMethods[] = {
    {"init", Danmaku_init, METH_VARARGS, ""},
    {"close", Danmaku_close, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};
static struct PyModuleDef danmakumodule = {
    PyModuleDef_HEAD_INIT,
    "danmaku",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,
    ModuleMethods
};

PyObject *createClassObject(const char *name, PyMethodDef methods[])
{
    PyObject *pClassName = PyUnicode_FromString(name);
    PyObject *pClassBases = PyTuple_New(0); // An empty tuple for bases is equivalent to `(object,)`
    PyObject *pClassDic = PyDict_New();


    PyMethodDef *def;
    // add methods to class
    for (def = methods; def->ml_name != NULL; def++)
    {
        PyObject *func = PyCFunction_New(def, NULL);
        PyObject *method = PyInstanceMethod_New(func);
        PyDict_SetItemString(pClassDic, def->ml_name, method);
        Py_DECREF(func);
        Py_DECREF(method);
    }

    // pClass = type(pClassName, pClassBases, pClassDic)
    PyObject *pClass = PyObject_CallFunctionObjArgs((PyObject *)&PyType_Type, pClassName, pClassBases, pClassDic, NULL);

    Py_DECREF(pClassName);
    Py_DECREF(pClassBases);
    Py_DECREF(pClassDic);

    return pClass;
}

PyMODINIT_FUNC PyInit_danmaku(void) {
    PyObject *module;
    module = PyModule_Create(&danmakumodule);
    PyObject* danmakuGroup = createClassObject("DanmakuGroup", DanmakuGroupMethods);
    PyModule_AddObject(module, "DanmakuGroup", danmakuGroup);
    return module;
}