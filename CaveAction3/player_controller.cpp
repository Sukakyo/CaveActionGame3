#include "player_controller.h"


namespace component {
	PlayerController::PlayerController(CAT_Rigidbody* const new_rigidbody, CAT_VirtualController* const new_v_controller, CAT_Animator2D* const new_animator2D) {
        this->m_rigidbody = new_rigidbody;
		this->m_virtual_controller = new_v_controller;
        this->m_animator2D = new_animator2D;
	}

	void PlayerController::set_input(CAT_Input*const new_input) {
		this->m_input = new_input;
	}

	void PlayerController::update() {
        int vertical = -(m_input->front - m_input->back);
        int horizontal = m_input->right - m_input->left;

        if (this->state == Move) {
            if (vertical == 1) {
                m_input->direction = Vector2i(0, 1);
            }
            else if (vertical == -1) {
                m_input->direction = Vector2i(0, -1);
            }
            else if (horizontal == 1) {
                m_input->direction = Vector2i(1, 0);
            }
            else if (horizontal == -1) {
                m_input->direction = Vector2i(-1, 0);
            }

            if (m_rigidbody->get_velocity().norm() > 50) {
                this->m_animator2D->change_animation(1, &(m_input->direction));
            }
            else {
                this->m_animator2D->change_animation(0, &(m_input->direction));
            }

            if (m_input->a == 1) {
                change_state(PlayerState::Attack);
            }
        }
        else if (this->state == Attack){

            this->m_animator2D->change_animation(2, &(m_input->direction));

            if (this->sum_time > 450) {
                change_state(PlayerState::Move);
            }
            
        }

        this->m_virtual_controller->input(Vector3d(horizontal, vertical, 0).normalized());
	}

    void PlayerController::gain(double delta_time) {
        this->sum_time += delta_time;
    }

    void PlayerController::change_state(PlayerState new_state) {
        this->state = new_state;
        this->sum_time = 0;
    }
}
