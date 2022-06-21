#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <glm/glm.hpp>

namespace Sage {
	enum class AccessFormat
	{
		Static,
		Streaming,
		Target
	};

	class Texture
	{
	public:
		static std::unique_ptr<Texture> Create(uint32_t width, uint32_t height);
		static std::unique_ptr<Texture> Create(uint32_t width, uint32_t height, AccessFormat format);
		static std::unique_ptr<Texture> Create(const std::string& path);
		virtual ~Texture() = 0 {};

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t getWidth() = 0;
		virtual uint32_t getHeight() = 0;
		virtual void setData(void* data) = 0;
		virtual void* GetRendererID() = 0;
	};

	class Serialiser;
	class TextureManager
	{
	public:
		static std::shared_ptr<Texture> load(const std::string& path);
		static std::shared_ptr<Texture> loadWhiteTexture();
	private:
		static std::unordered_map<std::string, std::shared_ptr<Texture>> loadedTextures;
		static std::shared_ptr<Texture> whiteTexture;
		
		friend class Serialiser;
	};

}