//
// Created by vantan on 2016/02/05.
//

#include <android/log.h>
#include <android/sensor.h>

#include <GLES3/gl31.h>
#include <EGL/egl.h>

#include <android_native_app_glue.h>
#include <string>
#include "Mylib/Component/renderer/LineRenderer.h"
#include "Mylib/GameObject.h"
#include "Mylib/Component/Camera.h"
#include "Mylib/Component/renderer/TriangleRenderer.h"
#include "Mylib/RendererManager.h"
#include "Mylib/Component/renderer/Material.h"
#include "Mylib/Component/renderer/Cube.h"
#include "Mylib/Component/renderer/Sphere.h"
#include "Mylib/Component/Transform.h"
#include "Mylib/Component/Actors.h"
#include "Mylib/Random.h"
#include "Mylib/Component/StarMover.h"

using namespace rew::system;

bool SphereOnSphere
        (
                const std::shared_ptr<Transform>& a,
                const std::shared_ptr<Transform>& b
        )
{
    auto a_pos = a->GetPos();
    auto b_pos = b->GetPos();

    auto vector = a_pos - b_pos;
    float distance = vector.dot(vector);
    float radius_sum = a->GetScale().x() * 0.5f + b->GetScale().x() * 0.5f;

    return distance <= radius_sum * radius_sum;
}

bool AABBOnSegment
        (
            const Eigen::Vector3f& start_point,
            const Eigen::Vector3f& end_point,
            const std::shared_ptr<Transform>& aabb
        )
{
    Eigen::Vector3f c = aabb->GetPos();
    Eigen::Vector3f e = aabb->GetScale() * 0.5f;
    Eigen::Vector3f m = (start_point + end_point) * 0.5f;
    Eigen::Vector3f d = end_point - m;
    m = m - c;

    float adx = std::abs(d.x());
    if(std::abs(m.x()) > e.x() + adx)return false;

    float ady = std::abs(d.y());
    if(std::abs(m.y()) > e.y() + ady)return false;

    float adz = std::abs(d.z());
    if(std::abs(m.z()) > e.z() + adz)return false;

    static const float EPSILON = 1.175494e-37;


    adx += EPSILON;
    ady += EPSILON;
    adx += EPSILON;

    if(std::abs(m.y() * d.z() - m.z() * d.y()) > e.y() * adz +e.z() * ady)return false;
    if(std::abs(m.z() * d.x() - m.x() * d.z()) > e.x() * adz +e.z() * adx)return false;
    if(std::abs(m.x() * d.y() - m.y() * d.x()) > e.x() * ady +e.y() * adx)return false;

    return true;

}

class Engine
{
public:

    Engine();
    Engine(android_app* app);

    static void EngineHandleCmd(
            android_app* app,
            khronos_int32_t cmd);

    static khronos_int32_t EngineHandleInput(
            android_app* app,
            AInputEvent* event);

    void TermDisplay();

    void ProcessSensors();
    void Update();
    void Draw();

    bool IsDestory()const{return !is_destory_;}

private:

    bool IsReady();


    void InitDisplay();
    void ResumeSensors();
    void SuspendSensors();
    void GetTouchPosition(android_app* app, AInputEvent* event);

    android_app* app_;

    ASensorManager* sensor_manager_;
    const ASensor* accelerometer_sensor_;
    ASensorEventQueue* sensor_event_queue_;

    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    khronos_int32_t width_;
    khronos_int32_t height_;
    float touch_x_;
    float touch_y_;
    float old_touch_x_;
    float old_touch_y_;
    float speed_x_;
    float speed_y_;


    bool has_focus_;
    bool is_created_window_;
    bool is_destory_;
    bool is_stop_;

    std::shared_ptr<GameObject> camera_;
    std::shared_ptr<Camera> camera_component_;
    std::shared_ptr<GameObject> cube_;
    renderer::Color<float>color_;
};

Engine::Engine():
app_(NULL),
sensor_manager_(NULL),
accelerometer_sensor_(NULL),
sensor_event_queue_(NULL),
has_focus_(false),
is_created_window_(false),
touch_x_(0.0f),
touch_y_(0.0f),
is_destory_(false),
old_touch_x_(0.0f),
old_touch_y_(0.0f),
is_stop_(false),
speed_x_(0.0f),
speed_y_(0.0f),
color_(0.0f, 0.0f, 0.0f, 1.0f)
{

}

Engine::Engine(android_app* app):
app_(app),
sensor_manager_(ASensorManager_getInstance()),
accelerometer_sensor_(ASensorManager_getDefaultSensor(
        sensor_manager_, ASENSOR_TYPE_ACCELEROMETER)),
sensor_event_queue_(ASensorManager_createEventQueue(
        sensor_manager_, app->looper, LOOPER_ID_USER,
        NULL, NULL)),
has_focus_(false),
is_created_window_(false),
touch_x_(0.0f),
touch_y_(0.0f),
is_destory_(false),
old_touch_x_(0.0f),
old_touch_y_(0.0f),
is_stop_(false),
speed_x_(0.0f),
speed_y_(0.0f),
color_(0.0f, 0.0f, 0.0f, 1.0f)
{
    app->userData = this;
    app->onAppCmd = &Engine::EngineHandleCmd;
    app->onInputEvent = &Engine::EngineHandleInput;
}

void Engine::EngineHandleCmd(
        android_app* app,
        khronos_int32_t cmd)
{
    auto engine = reinterpret_cast<Engine*>(app->userData);
    switch( cmd )
    {
        case APP_CMD_SAVE_STATE:
            engine->is_stop_= true;
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "SAVE");
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if( app->window == NULL )return;
            engine->InitDisplay();
//            engine->Draw();
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "INIT_WINDOW");
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            engine->TermDisplay();
            engine->has_focus_ = false;
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "DESTORY");
            break;
        case APP_CMD_STOP:
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "STOP");
            break;
        case APP_CMD_GAINED_FOCUS:
            engine->ResumeSensors();
            //Start animation
            engine->has_focus_ = true;
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "INPUT_ON");
            break;
        case APP_CMD_LOST_FOCUS:
            engine->SuspendSensors();
            // Also stop animating.
            engine->has_focus_ = false;
//            engine->Draw();
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "INPUT_OFF");
            break;
        case APP_CMD_LOW_MEMORY:
            //Free up GL resources
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "MEMORY");
            break;
    }
}

khronos_int32_t Engine::EngineHandleInput(
        android_app* app,
        AInputEvent* event)
{
    auto engine = reinterpret_cast<Engine*>(app->userData);
    int type = AInputEvent_getType(event);
    if(type == AINPUT_EVENT_TYPE_MOTION )
    {
        engine->GetTouchPosition(app, event);
        return 1;
    }
    return 0;
}

void Engine::TermDisplay()
{
    if (display_ != EGL_NO_DISPLAY) {
        eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context_ != EGL_NO_CONTEXT) {
            eglDestroyContext(display_, context_);
        }
        if (surface_ != EGL_NO_SURFACE) {
            eglDestroySurface(display_, surface_);
        }
        eglTerminate(display_);
    }

    display_ = EGL_NO_DISPLAY;
    context_ = EGL_NO_CONTEXT;
    surface_ = EGL_NO_SURFACE;
}

bool Engine::IsReady()
{
    return has_focus_;
}

void Engine::InitDisplay()
{

    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);


    ANativeWindow_setBuffersGeometry(app_->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, app_->window, NULL);

    const EGLint context_attribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, //Request opengl ES2.0
                                       EGL_NONE };

    context = eglCreateContext(display, config, NULL, context_attribs);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
        return;

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    display_ = display;
    context_ = context;
    surface_ = surface;
    width_ = w;
    height_ = h;

    touch_x_ = width_ * 0.5f;
    touch_y_ = height_ * 0.5f;

    old_touch_x_ = width_ * 0.5f;
    old_touch_y_ = height_ * 0.5f;

    is_stop_ = false;

    if(!is_created_window_)
    {
        glEnable(GL_DEPTH_TEST);
        glEnable( GL_CULL_FACE );

        is_created_window_ = true;

        float aspect = width_ / static_cast<float>(height_);

        camera_ = GameObject::Create("Camera");
        camera_->GetTransform()->SetPos(Eigen::Vector3f(0,0,5));
        auto camera_component = std::make_shared<Camera>(*camera_.get());
        camera_component_ = camera_component;
        camera_component_->SetPerspective(45, aspect, 0.1f, 100.0f);
        float camera_scale = 0.02f;
        camera_->GetTransform()->SetScale(Eigen::Vector3f(camera_scale, camera_scale, camera_scale));

        auto cube = GameObject::Create("Cube");
        auto material = renderer::Material(ShaderType::BASIC, 1.0f, 1.0f, 0.0f, 1.0f);
        auto mesh = std::make_shared<renderer::Sphere>();
        auto ren = renderer::LineRenderer::Create(*cube.get(), material, mesh);
        auto actor = std::make_shared<Actors>(*cube.get());
        cube->AddComponent(ren);
        cube->AddComponent(actor);
        cube_ = cube;
    }
}

void Engine::ResumeSensors()
{
    if(accelerometer_sensor_ == NULL)return;
    ASensorEventQueue_enableSensor( sensor_event_queue_, accelerometer_sensor_ );
    // We'd like to get 60 events per second (in us).
    ASensorEventQueue_setEventRate( sensor_event_queue_, accelerometer_sensor_,
                                    (1000L / 60) * 1000 );
}

void Engine::SuspendSensors()
{
    if(accelerometer_sensor_ == NULL)return;
    ASensorEventQueue_disableSensor( sensor_event_queue_, accelerometer_sensor_ );
}

void Engine::GetTouchPosition(android_app* app, AInputEvent* event)
{
    auto engine = reinterpret_cast<Engine*>(app->userData);
    int action = AMotionEvent_getAction(event);

    static bool is_touch = false;

    if(action != AKEY_EVENT_ACTION_UP)
    {
        engine->touch_x_ = AMotionEvent_getX(event, 0);
        engine->touch_y_ = AMotionEvent_getY(event, 0);

        if(is_touch)
        {
            engine->speed_x_ = -(engine->old_touch_x_ - engine->touch_x_);
            engine->speed_y_ = (engine->old_touch_y_ - engine->touch_y_);

            float handling = 3.0f;

            if(engine->speed_x_ < handling && engine->speed_x_ > -handling)
            {
                engine->speed_x_ = 0;
            }

            if(engine->speed_y_ < handling && engine->speed_y_ > -handling)
            {
                engine->speed_y_ = 0;
            }

        }

        engine->old_touch_x_ = engine->touch_x_;
        engine->old_touch_y_ = engine->touch_y_;

        is_touch = true;
    }
    else
    {
        engine->speed_x_ =0.0f;
        engine->speed_y_ =0.0f;
        is_touch = false;
    }
}

void Engine::ProcessSensors()
{
    int id;
    int events;
    android_poll_source* source;


    while(id = ALooper_pollAll(
            IsReady(), NULL, &events,
            reinterpret_cast<void**>(&source))
               >= 0)
    {
        if(source != NULL) source->process(app_, source);

        if(id != LOOPER_ID_USER)break;
        if(accelerometer_sensor_ == NULL)break;

        ASensorEvent event;
        while (ASensorEventQueue_getEvents(sensor_event_queue_, &event, 1) > 0)
        {
            // センサーの情報を取得可
        }
    }
}

void Engine::Update()
{

    if(!IsReady()) return;
    if(is_stop_)
        return;

    GameObject::GetTask().Update();

    static unsigned long count = 0;
    count++;

    std::uniform_real_distribution<float>rand(0.0f, 1.0f);

    if(count % (60 * 7) == 0)
    {


        auto cube = GameObject::Create("Sphere");
        auto material = renderer::Material(ShaderType::BASIC, rand(Actors::GetRandom()), rand(Actors::GetRandom()), rand(Actors::GetRandom()), 1.0f);
        auto mesh = std::make_shared<renderer::Sphere>();
        auto ren = renderer::LineRenderer::Create(*cube.get(), material, mesh);
        auto actor = std::make_shared<Actors>(*cube.get());
        cube->AddComponent(ren);
        cube->AddComponent(actor);

        auto spawn_pos = camera_->GetTransform()->GetPos() + camera_->GetTransform()->GetDirection() * 15 + Eigen::Vector3f(Random::RandomRange(-0.5f, 0.5f), Random::RandomRange(-0.5f, 0.5f), 0.0f);
        cube->GetTransform()->SetPos(spawn_pos);
    }

    if(count % (60 * 3) == 0)
    {
        auto cube = GameObject::Create("Cube");
        auto material = renderer::Material(ShaderType::BASIC, rand(Actors::GetRandom()), rand(Actors::GetRandom()), rand(Actors::GetRandom()), 1.0f);
        auto mesh = std::make_shared<renderer::Cube>();
        auto ren = renderer::LineRenderer::Create(*cube.get(), material, mesh);
        auto actor = std::make_shared<Actors>(*cube.get());
        cube->AddComponent(ren);
        cube->AddComponent(actor);

        auto spawn_pos = camera_->GetTransform()->GetPos() + camera_->GetTransform()->GetDirection() * 15 + Eigen::Vector3f(Random::RandomRange(-0.5f, 0.5f), Random::RandomRange(-0.5f, 0.5f), 0.0f);
        cube->GetTransform()->SetPos(spawn_pos);
    }

    if(count % (10) == 0)
    {
        auto cube = GameObject::Create("SphereParticle");
        auto material = renderer::Material(ShaderType::BASIC, rand(Actors::GetRandom()), rand(Actors::GetRandom()), rand(Actors::GetRandom()), 1.0f);
        auto mesh = std::make_shared<renderer::Sphere>();
        auto ren = renderer::TriangleRenderer::Create(*cube.get(), material, mesh);
        auto mover = std::make_shared<StarMover>(*cube.get());
        cube->AddComponent(ren);
        cube->AddComponent(mover);

        auto spawn_pos = camera_->GetTransform()->GetPos() +
                camera_->GetTransform()->GetDirection() * 15 +
                Eigen::Vector3f(Random::RandomRange(-1.0f, 1.0f), Random::RandomRange(-1.0f, 1.0f), 0.0f);
        cube->GetTransform()->SetPos(spawn_pos)->SetScale(Eigen::Vector3f::Ones() * 0.01f);
    }


    static float speed_z = -0.05f;
    speed_z -= -0.000001f;

    camera_->GetTransform()->Translate(Eigen::Vector3f(speed_x_ * 0.01f, speed_y_ * 0.01f, speed_z));

    auto camera_pos = camera_->GetTransform()->GetPos();

    float max= 1;

    if(camera_pos.x() > max)
    {
        camera_->GetTransform()->SetPos(Eigen::Vector3f(max,camera_pos.y(),camera_pos.z()));
    }
    else if(camera_pos.x() < -max)
    {
        camera_->GetTransform()->SetPos(Eigen::Vector3f(-max,camera_pos.y(),camera_pos.z()));
    }

    if(camera_pos.y() > max)
    {
        camera_->GetTransform()->SetPos(Eigen::Vector3f(camera_pos.x(),max,camera_pos.z()));
    }
    else if(camera_pos.y() < -max)
    {
        camera_->GetTransform()->SetPos(Eigen::Vector3f(camera_pos.x(),-max,camera_pos.z()));
    }

    auto cube_hash = std::hash<std::string>()("Cube");
    auto sphere_hash = std::hash<std::string>()("Sphere");

    auto lp_matrix = camera_component_->Perspective() * camera_component_->LookAt();

    for(const auto& object : GameObject::GetTask().GetList())
    {
        if(!(std::hash<std::string>()(object->GetName()) == cube_hash ||
             std::hash<std::string>()(object->GetName()) == sphere_hash))continue;

        if(!SphereOnSphere(object->GetTransform(), camera_->GetTransform()))continue;

        auto ren = object->GetComponent<renderer::LineRenderer>();
        const auto& mesh = ren->GetMesh();
        auto vertices = mesh->GetVertices();
        auto indices = mesh->GetIndices();
        std::vector<Eigen::Vector3f> position;
        auto wlp_matrix = lp_matrix * object->GetTransform()->GetWorldMatrix();
        for(int i = 0; i < vertices.size(); i += 3)
        {
            Eigen::Vector4f pos = wlp_matrix * Eigen::Vector4f(vertices[i], vertices[i + 1], vertices[i + 2], 1.0f);
            position.emplace_back(Eigen::Vector3f(pos.x(), pos.y(), pos.z()));
        }
        for(int i = 0; i < indices.size(); i += 2)
        {
            if(!AABBOnSegment(position[i], position[i + 1], camera_->GetTransform()))continue;
            is_destory_ = true;
            color_ = renderer::Color<float>(1.0f, 0.0f, 0.0f, 1.0f);
            __android_log_print(ANDROID_LOG_DEBUG, "DEBGU", "HIT");
        }
    }
}

void Engine::Draw()
{
    if(!IsReady()) return;
    if(is_stop_)
        return;
    glClearColor(color_.GetRed(), color_.GetGreen(), color_.GetBlue(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float aspect = width_ / static_cast<float>(height_);

    renderer::Renderer::GetRendererManager().Update(*camera_component_);

    eglSwapBuffers(display_,surface_);
}

void android_main(android_app* app)
{
    app_dummy();

    Engine engine(app);


    while (app->destroyRequested == 0 && engine.IsDestory())
    {
        engine.ProcessSensors();

        engine.Update();

        engine.Draw();

    }
    __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "FINAL");
    engine.TermDisplay();
}
