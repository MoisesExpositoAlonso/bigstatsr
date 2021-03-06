################################################################################

context("UNIV_LIN_REG")

# Simulating some data
N <- 73
M <- 43
x <- matrix(rnorm(N * M, mean = 100, sd = 5), N)
y <- rnorm(N)

covar0 <- matrix(rnorm(N * 3), N)
lcovar <- list(NULL, covar0)

################################################################################

getLM <- function(X, y, covar, ind = NULL) {
  res <- matrix(NA, M, 4)
  for (i in 1:M) {
    mod <- lm(y ~ cbind(X[, i, drop = FALSE], covar), subset = ind)
    res[i, ] <- summary(mod)$coefficients[2, ]
  }
  res
}

################################################################################

test_that("equality with lm with all data", {
  for (t in TEST.TYPES) {
    X <- `if`(t == "raw", asFBMcode(x), big_copy(x, type = t))

    for (covar in lcovar) {
      mod <- big_univLinReg(X, y, covar.train = covar, ncores = test_cores())
      mod$p.value <- predict(mod, log10 = FALSE)
      expect_equivalent(as.matrix(mod), getLM(X, y, covar))

      p <- plot(mod, type = sample(c("Manhattan", "Q-Q", "Volcano"), 1))
      expect_s3_class(p, "ggplot")
    }
  }
})

################################################################################

test_that("equality with lm with only half the data", {
  ind <- sample(N, N / 2)

  for (t in TEST.TYPES) {
    X <- `if`(t == "raw", asFBMcode(x), big_copy(x, type = t))

    for (covar in lcovar) {
      mod <- big_univLinReg(X, y.train = y[ind],
                            covar.train = covar[ind, ],
                            ind.train = ind,
                            ncores = test_cores())
      mod$p.value <- predict(mod, log10 = FALSE)
      expect_equivalent(as.matrix(mod), getLM(X, y, covar, ind))

      p <- plot(mod, type = sample(c("Manhattan", "Q-Q", "Volcano"), 1))
      expect_s3_class(p, "ggplot")
    }
  }
})

################################################################################
