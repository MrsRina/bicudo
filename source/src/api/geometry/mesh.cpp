#include "bicudo/api/geometry/mesh.hpp"

void bicudo::mesh::append(const std::vector<float> &list, bicudo::meshing meshing) {
	switch (meshing) {
		case bicudo::meshing::vertex: {
			this->v.insert(this->v.cend(), list.cbegin(), list.cend());
			break;
		}

		case bicudo::meshing::texture: {
			this->t.insert(this->t.cend(), list.cbegin(), list.cend());
			break;
		}

		case bicudo::meshing::normal: {
			this->vn.insert(this->vn.cend(), list.cbegin(), list.cend());
			break;
		}
	}
}

void bicudo::mesh::append(const std::vector<uint32_t> &list, bicudo::meshing meshing) {
	switch (meshing) {
		case bicudo::meshing::ivertex: {
			this->iv.insert(this->iv.cend(), list.cbegin(), list.cend());
			break;
		}

		case bicudo::meshing::itexture: {
			this->it.insert(this->it.cend(), list.cbegin(), list.cend());
			break;
		}

		case bicudo::meshing::inormal: {
			this->ivn.insert(this->ivn.cend(), list.cbegin(), list.cend());
			break;
		}
	}
}

void bicudo::mesh::set_vec_len(int32_t len, bicudo::meshing meshing) {
	switch (meshing) {
		case bicudo::meshing::vertex: {
			this->v_vec_len = len;
			break;
		}

		case bicudo::meshing::texture: {
			this->t_vec_len = len;
			break;
		}

		case bicudo::meshing::normal: {
			this->vn_vec_len = len;
			break;
		}
	}
}

std::vector<float> &bicudo::mesh::get_position_mesh(bicudo::meshing meshing) {
	switch (meshing) {
		case bicudo::meshing::vertex: {
			return this->v;
		}

		case bicudo::meshing::texture: {
			return this->t;
		}

		case bicudo::meshing::normal: {
			return this->vn;
		}
	}

	return this->v;
}

std::vector<uint32_t> &bicudo::mesh::get_index_mesh(bicudo::meshing meshing) {
	switch (meshing) {
		case bicudo::meshing::ivertex: {
			return this->iv;
		}

		case bicudo::meshing::itexture: {
			return this->it;
		}

		case bicudo::meshing::inormal: {
			return this->ivn;
		}
	}

	return this->iv;
}

int32_t bicudo::mesh::get_vec_len(bicudo::meshing meshing) {
	switch (meshing) {
		case bicudo::meshing::vertex: {
			return this->v_vec_len;
		}

		case bicudo::meshing::texture: {
			return this->t_vec_len;
		}

		case bicudo::meshing::normal: {
			return this->vn_vec_len;
		}
	}

	return 0;
}