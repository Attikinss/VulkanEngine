#pragma once

namespace VKE {
	class NonCopyable {
	public:
		NonCopyable() = default;
		virtual ~NonCopyable() = default;

		NonCopyable(const NonCopyable&) = delete;
		NonCopyable operator=(const NonCopyable&) = delete;
	};
}