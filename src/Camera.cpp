#include <Camera.h>

Camera::Camera(const int width, const int height, const glm::vec3 &position) {
    m_StartPosition = position;
    Set(width, height, position);
}

void Camera::Set(const int width, const int height, const glm::vec3 &position) {
    m_IsPerspective = true;
    m_Yaw           = YAW;
    m_Pitch         = PITCH;

    m_FoVy   = FOV;
    m_Width  = width;
    m_Height = height;
    m_ZNear  = zNEAR;
    m_ZFar   = zFAR;

    m_WorldUp  = glm::vec3(0, 1, 0);
    m_Position = position;

    m_LastX          = static_cast<float>(width) / 2.0f;
    m_LastY          = static_cast<float>(height) / 2.0f;
    m_FirstMouseMove = true;

    UpdateCameraVectors();
}

void Camera::SetPosition(const glm::vec3 &position) {
    m_Position = position;
    UpdateCameraVectors();
}

void Camera::LookAt(const glm::vec3 &targetPoint, const glm::vec3 &up) {
    m_Forward = glm::normalize(targetPoint - m_Position);
    m_Right   = glm::normalize(glm::cross(m_Forward, up));
    m_Up      = glm::normalize(glm::cross(m_Right, m_Forward));
}

void Camera::Reset(const int width, const int height) { Set(width, height, m_StartPosition); }

void Camera::Reshape(const int windowWidth, const int windowHeight) {
    m_Width  = windowWidth;
    m_Height = windowHeight;

    glViewport(0, 0, windowWidth, windowHeight);
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

const glm::vec3 &Camera::GetPosition() const { return m_Position; }

glm::mat4 Camera::GetProjectionMatrix() const {
    if (m_IsPerspective) {
        const float aspectRatio = static_cast<float>(m_Width) / static_cast<float>(m_Height);
        return glm::perspective(glm::radians(m_FoVy), aspectRatio, m_ZNear, m_ZFar);
    }

    constexpr float scaleFactor = 2000.f;
    return glm::ortho<float>(static_cast<float>(-m_Width) / scaleFactor,
                             static_cast<float>(m_Width) / scaleFactor,
                             static_cast<float>(-m_Height) / scaleFactor,
                             static_cast<float>(m_Height) / scaleFactor, -m_ZFar, m_ZFar);
}

void Camera::ProcessKeyboard(const CameraMovementType &direction, const float deltaTime) {
    const auto velocity = m_CameraSpeed * deltaTime;
    switch (direction) {
        case FORWARD:
            m_Position += m_Forward * velocity;
            break;
        case BACKWARD:
            m_Position -= m_Forward * velocity;
            break;
        case LEFT:
            m_Position -= m_Right * velocity;
            break;
        case RIGHT:
            m_Position += m_Right * velocity;
            break;
        case UP:
            m_Position += m_Up * velocity;
            break;
        case DOWN:
            m_Position -= m_Up * velocity;
            break;
        default:
            break;
    }
}

void Camera::MouseControl(const float xPos, const float yPos) {
    if (m_FirstMouseMove) {
        m_LastX          = xPos;
        m_LastY          = yPos;
        m_FirstMouseMove = false;
    }

    float xChange = xPos - m_LastX;
    float yChange = m_LastY - yPos;
    m_LastX       = xPos;
    m_LastY       = yPos;

    if (std::fabs(xChange) <= 1e-6 && std::fabs(yChange) <= 1e-6) {
        return;
    }

    xChange *= m_MouseSensitivity;
    yChange *= m_MouseSensitivity;

    ProcessMouseMovement(xChange, yChange);
}

void Camera::ProcessMouseScroll(const float yOffset) {
    if (m_FoVy >= 1.0f && m_FoVy <= 90.0f)
        m_FoVy -= yOffset;

    if (m_FoVy <= 1.0f)
        m_FoVy = 1.0f;

    if (m_FoVy >= 90.0f)
        m_FoVy = 90.0f;
}

void Camera::ProcessMouseMovement(const float xOffset, const float yOffset) {
    m_Yaw += xOffset;
    m_Pitch += yOffset;

    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors() {
    this->m_Forward.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    this->m_Forward.y = sin(glm::radians(m_Pitch));
    this->m_Forward.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    this->m_Forward   = glm::normalize(this->m_Forward);
    m_Right           = glm::normalize(glm::cross(m_Forward, m_WorldUp));

    m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
}
