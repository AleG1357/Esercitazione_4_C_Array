#pragma once

#include <iostream>

bool ImportData(const std::string& inputFilePath,
                double& S,
                size_t& n,
                double*& w,
                double*& r);

double ComputePortfolioReturn(const size_t& n,
                              const double* const& w,
                              const double* const& r);

bool ExportResult(const std::string& outputFilePath,
                  const double& S,
                  const size_t& n,
                  const double* const& w,
                  const double* const& r,
                  const double& portfolioRate);
