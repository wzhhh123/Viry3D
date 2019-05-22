/*
* Viry3D
* Copyright 2014-2019 by Stack - stackos@qq.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once

#include "D3D11Driver.h"
#include "D3D11Context.h"

namespace filament
{
	namespace backend
	{
		struct D3D11SwapChain : public HwSwapChain 
		{
			D3D11SwapChain(D3D11Context* context, void* native_window);
			~D3D11SwapChain();

			IDXGISwapChain3* swap_chain = nullptr;
			ID3D11RenderTargetView1* color_view = nullptr;
		};

		struct D3D11RenderTarget : public HwRenderTarget
		{
			D3D11RenderTarget(
				D3D11Context* context,
				TargetBufferFlags flags,
				uint32_t width,
				uint32_t height,
				uint8_t samples,
				TargetBufferInfo color,
				TargetBufferInfo depth,
				TargetBufferInfo stencil);
			explicit D3D11RenderTarget(D3D11Context* context);
			~D3D11RenderTarget();
			void CreateDepth(D3D11Context* context, DXGI_FORMAT format, uint32_t width, uint32_t height);

			bool default_render_target = false;
			ID3D11RenderTargetView1* color_view = nullptr;
			ID3D11DepthStencilView* depth_view = nullptr;
		};

		struct D3D11Program : public HwProgram
		{
			D3D11Program(D3D11Context* context, Program&& program);
			~D3D11Program();

			ID3D11VertexShader* vertex_shader = nullptr;
			ID3D11PixelShader* pixel_shader = nullptr;
		};

		struct D3D11UniformBuffer : public HwUniformBuffer
		{
			D3D11UniformBuffer(D3D11Context* context, size_t size, BufferUsage usage);
			~D3D11UniformBuffer();
			void Load(D3D11Context* context, const BufferDescriptor& data);

			ID3D11Buffer* buffer = nullptr;
			size_t size;
			BufferUsage usage;
		};

		struct D3D11SamplerGroup : public HwSamplerGroup
		{
			D3D11SamplerGroup(D3D11Context* context, size_t size);
			~D3D11SamplerGroup();
			void Update(D3D11Context* context, SamplerGroup&& sg);
		};

		struct D3D11Texture : public HwTexture
		{
			D3D11Texture(
				D3D11Context* context,
				backend::SamplerType target,
				uint8_t levels,
				TextureFormat format,
				uint8_t samples,
				uint32_t width,
				uint32_t height,
				uint32_t depth,
				TextureUsage usage);
			~D3D11Texture();
			void Update2DImage(
				D3D11Context* context,
				uint32_t level,
				uint32_t x,
				uint32_t y,
				uint32_t width,
				uint32_t height,
				const PixelBufferDescriptor& data);
			void UpdateCubeImage(
				D3D11Context* context,
				uint32_t level,
				const PixelBufferDescriptor& data,
				FaceOffsets face_offsets);
			void GenerateMipmaps(D3D11Context* context);

			ID3D11Texture2D1* texture = nullptr;
			ID3D11ShaderResourceView1* image_view = nullptr;
		};

		struct D3D11VertexBuffer : public HwVertexBuffer
		{
			D3D11VertexBuffer(
				D3D11Context* context,
				uint8_t buffer_count,
				uint8_t attribute_count,
				uint32_t vertex_count,
				AttributeArray attributes,
				BufferUsage usage);
			~D3D11VertexBuffer();
			void Update(
				D3D11Context* context,
				size_t index,
				const BufferDescriptor& data,
				uint32_t offset);

			std::vector<ID3D11Buffer*> buffers;
			BufferUsage usage;
		};

		struct D3D11IndexBuffer : public HwIndexBuffer
		{
			D3D11IndexBuffer(
				D3D11Context* context,
				ElementType element_type,
				uint32_t index_count,
				BufferUsage usage);
			~D3D11IndexBuffer();
			void Update(
				D3D11Context* context,
				const BufferDescriptor& data,
				uint32_t offset);

			ID3D11Buffer* buffer = nullptr;
			BufferUsage usage;
		};
	}
}
