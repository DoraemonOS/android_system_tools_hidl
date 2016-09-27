/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ARRAY_TYPE_H_

#define ARRAY_TYPE_H_

#include "Type.h"

#include <vector>

namespace android {

struct ConstantExpression;

struct ArrayType : public Type {
    // Extends existing array by adding another dimension.
    ArrayType(ArrayType *srcArray, ConstantExpression *size);

    ArrayType(Type *elementType, ConstantExpression *size);

    static ArrayType *AddDimension(ArrayType *base, ConstantExpression *size);

    bool isArray() const override;

    void addDimension(ConstantExpression *size);

    std::string getCppType(StorageMode mode,
                           std::string *extra,
                           bool specifyNamespaces) const override;

    void addNamedTypesToSet(std::set<const FQName> &set) const override;

    std::string getJavaType(
            std::string *extra, bool forInitializer) const override;

    void emitReaderWriter(
            Formatter &out,
            const std::string &name,
            const std::string &parcelObj,
            bool parcelObjIsPointer,
            bool isReader,
            ErrorMode mode) const override;

    void emitReaderWriterEmbedded(
            Formatter &out,
            size_t depth,
            const std::string &name,
            bool nameIsPointer,
            const std::string &parcelObj,
            bool parcelObjIsPointer,
            bool isReader,
            ErrorMode mode,
            const std::string &parentName,
            const std::string &offsetText) const override;

    bool needsEmbeddedReadWrite() const override;

    void emitJavaReaderWriter(
            Formatter &out,
            const std::string &parcelObj,
            const std::string &argName,
            bool isReader) const override;

    void emitJavaFieldInitializer(
            Formatter &out, const std::string &fieldName) const override;

    void emitJavaFieldReaderWriter(
            Formatter &out,
            size_t depth,
            const std::string &parcelName,
            const std::string &blobName,
            const std::string &fieldName,
            const std::string &offset,
            bool isReader) const override;

    status_t emitVtsTypeDeclarations(Formatter &out) const override;

    bool isJavaCompatible() const override;

    void getAlignmentAndSize(size_t *align, size_t *size) const override;

private:
    Type *mElementType;
    std::vector<size_t> mSizes;
    std::vector<std::string> mSizeComments;

    DISALLOW_COPY_AND_ASSIGN(ArrayType);
};

}  // namespace android

#endif  // ARRAY_TYPE_H_

