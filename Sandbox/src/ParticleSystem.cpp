#include "gxpch.h"

#include "ParticleSystem.h"

#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

ParticleSystem::ParticleSystem(uint32_t maxParticles)
{
	m_PoolIndex = maxParticles - 1;
	m_ParticlePool.resize(maxParticles);
}

void ParticleSystem::OnUpdate(Galaxy::Timestep ts)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= ts;
		particle.Position += particle.Velocity * (float)ts;
		particle.Rotation += 0.01f * (float)ts;
	}
}

void ParticleSystem::OnRender(Galaxy::OrthographicCamera& camera)
{
	Galaxy::Renderer2D::BeginScene(camera);
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		//Fade away particles
		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorBegin, particle.ColorEnd, life);

		float size = glm::lerp(particle.SizeBegin, particle.SizeEnd, life);

		Galaxy::Renderer2D::DrawRotatedQuad({ particle.Position.x, particle.Position.y, 1.0f }, { size, size }, particle.Rotation, color);
	}
	Galaxy::Renderer2D::EndScene();
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	//Setup
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

	//Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
	particle.Velocity.y += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);

	//Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	//Lifetime
	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}

